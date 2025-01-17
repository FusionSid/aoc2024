import shutil
import webbrowser
from pathlib import Path
from os import path, environ, mkdir

import typer
import dotenv
import requests
from rich import print


SRC_DIR = path.join(path.dirname(__file__), "src")


def save_input(day: str, dir_path: str) -> None:
    URL = f"https://adventofcode.com/2024/day/{day}/input"
    SESSION_COOKIE = environ.get("SESSION")

    print("[green]Fetching Input Data...")
    response = requests.get(
        URL,
        headers={"cookie": f"session={SESSION_COOKIE}"},
    )
    # raise exception if failed to fetch
    response.raise_for_status()

    with open(path.join(dir_path, "input.txt"), "w") as f:
        f.write(response.text.strip())


def main(day: str):
    DIRECTORY = path.join(SRC_DIR, f"day{int(day):02d}")
    TEMPLATE_DIR = path.join(SRC_DIR, "utils/")

    mkdir(DIRECTORY)
    print("[b green]Created Directory For Day!")

    save_input(day, DIRECTORY)
    print("[b green]Input Data Saved!")

    Path(path.join(DIRECTORY, "test.txt")).touch()

    original_path = path.join(TEMPLATE_DIR, "template.cpp")
    for original in ["p1.cpp", "p2.cpp"]:
        shutil.copyfile(original_path, path.join(DIRECTORY, original))

    print("[b green]All Files Created!")

    print("[b green]Setup Complete! Opening Challenge In Browser...")
    webbrowser.open(f"https://adventofcode.com/2024/day/{day}")


if __name__ == "__main__":
    dotenv.load_dotenv()
    typer.run(main)
