from __future__ import annotations


def hello_string(name: str | None = None) -> str:
    if name:
        return f"Hello {name}!"
    return "Hello World!"
