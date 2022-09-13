# Template Repository: Python

Use this repository as a template for creating new Python-based repositories.

## Development

Make sure you have [Python prerequisites](https://www.notion.so/fathomradiant/Python-Development-8d35a7b285c34dd984556a4fcd6f6346)
set up first.

To automatically run checks on changes as you try to commit them:
```
pre-commit install
```

### Run tests

```
poetry run tox
```

### Run linters

```
poetry run tox -e lint
```
