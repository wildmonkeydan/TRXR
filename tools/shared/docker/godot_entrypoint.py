import argparse
import os
import shutil
from dataclasses import dataclass, field, fields
from pathlib import Path
from subprocess import check_call, run
from typing import Any, Self

from shared.packaging import create_zip
from shared.paths import TOOLS_DIR
from shared.versioning import generate_package_name, generate_version


@dataclass
class BaseOptions:
    platform: str

    @property
    def version(self) -> str:
        return generate_version()

    @property
    def build_root(self) -> Path:
        return Path(f"/app/godot/")

    @classmethod
    def from_args(cls, args: argparse.Namespace) -> Self:
        cls_fields = [field.name for field in fields(cls)]
        filtered_args = vars(args)
        filtered_args = {
            k: v for k, v in filtered_args.items() if k in cls_fields
        }
        return cls(**filtered_args)


@dataclass
class PackageOptions(BaseOptions):
    platform: str

    @property
    def default_stem(self) -> str:
        return generate_package_name(
            engine_version=self.version,
            platform=self.platform,
        )

    @property
    def ship_dirs(self) -> list[Path]:
        if self.platform == "win-installer":
            return []
        return [Path("/app/data/trx/ship/")]

    @property
    def release_zip_files(self) -> list[tuple[Path, str]]:
        if self.platform == "linux":
            return [(self.build_root / "TRX", "TRX")]

        return []


@dataclass
class BuildOptions(BaseOptions):
    target: str
    meson_args: list[str] = field(default_factory=list)

    strip_tool = "strip"
    upx_tool = "upx"

    @property
    def build_args(self) -> list[str]:
        if self.platform == "win":
            return [
                "--cross",
                "/app/tools/shared/docker/game-win/meson_linux_mingw32.txt",
            ]
        return []

    @property
    def compressable_exes(self) -> list[Path]:
        return []

    @property
    def build_target(self) -> Path:
        return Path(f"src/")


def compress_exe(options: BuildOptions, path: Path) -> None:
    if run([options.upx_tool, "-t", str(path)]).returncode != 0:
        check_call([options.strip_tool, str(path)])
        check_call([options.upx_tool, str(path)])


class BaseCommand:
    name: str = NotImplemented
    # argparse reads this as a boolean, which NotImplemented refuses to be
    help: str | None = None

    def decorate_parser(self, parser: argparse.ArgumentParser) -> None:
        pass

    def run(self, args: argparse.Namespace) -> None:
        raise NotImplementedError("not implemented")


class BuildCommand(BaseCommand):
    name = "build"

    def decorate_parser(self, parser: argparse.ArgumentParser) -> None:
        parser.add_argument("--platform")
        parser.add_argument(
            "--target",
            choices=["editor", "template_release", "template_debug"],
            required=True,
        )

    def run(self, args: argparse.Namespace) -> None:
        options = BuildOptions.from_args(args)
        check_call(["scons", f"platform={options.platform}", f"target={options.target}"], cwd=options.build_root)


class PackageCommand(BaseCommand):
    name = "package"

    def decorate_parser(self, parser: argparse.ArgumentParser) -> None:
        parser.add_argument("--platform")
        parser.add_argument("-o", "--output", type=Path)
        parser.add_argument("--no-zip", action="store_true")

    def run(self, args: argparse.Namespace) -> None:
        options = PackageOptions.from_args(args)
        run_package(options=options, output=args.output, no_zip=args.no_zip)


def run_package(
        options: PackageOptions, output: Path | None, no_zip: bool
) -> None:
    if output:
        zip_path = output
        if zip_path.suffix.lower() != ".zip" and not no_zip:
            zip_path /= options.default_stem + ".zip"
    else:
        zip_path = Path()
        if no_zip:
            zip_path /= options.default_stem
        else:
            zip_path /= options.default_stem + ".zip"

    source_files: list[tuple[Path, str] | Path] = []

    for ship_dir in options.ship_dirs:
        stack = [ship_dir]
        while stack:
            current = stack.pop()
            for item in current.iterdir():
                try:
                    real = item.resolve(strict=True)
                except FileNotFoundError:
                    continue  # broken link, ignore
                if real.is_file():
                    source_files.append((real, str(item.relative_to(ship_dir))))
                elif real.is_dir():
                    stack.append(item)

    for path in options.release_zip_files:
        source_files.append(path)

    if no_zip:
        for src_path, dst_name in source_files:
            dst_path = zip_path / dst_name
            dst_path.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy(src_path, dst_path)
    else:
        zip_path.parent.mkdir(parents=True, exist_ok=True)
        create_zip(zip_path, source_files)
    print(f"Created {zip_path}")


def parse_args(
        commands: dict[str, BaseCommand], **kwargs
) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Docker entrypoint")
    subparsers = parser.add_subparsers(dest="action", help="Subcommands")
    parser.set_defaults(action="build", command=commands["build"])
    parser.set_defaults(**kwargs)

    for command in commands.values():
        subparser = subparsers.add_parser(command.name, help=command.help)
        command.decorate_parser(subparser)
        subparser.set_defaults(command=command)
        subparser.set_defaults(**kwargs)
    result = parser.parse_args()
    return result


def main(**kwargs: Any) -> None:
    commands = {
        command_cls.name: command_cls()
        for command_cls in BaseCommand.__subclasses__()
    }
    args = parse_args(commands, **kwargs)
    args.command.run(args)
