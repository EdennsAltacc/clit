
# Contributing to CLIT

Thanks for your interest in contributing to CLIT.

CLIT is a small command-line toolchain focused on making common terminal tasks simpler and faster. Contributions are welcome.

## Getting Started

Clone the repository:

```sh
git clone https://github.com/EdennsAltacc/clit.git
cd clit
```

Build the project:

```sh
gcc src/clit.c -o build/clit -lcurl
```

## Making Changes

Before making a change, create a new branch:

```sh
git checkout -b your-branch-name
```

Keep changes focused and avoid mixing unrelated changes into the same pull request.

When adding a new command, make sure it:

* Has a clear purpose
* Fits the goals of CLIT
* Handles invalid input reasonably
* Works on supported platforms where possible
* Is documented in `README.md`

## Testing

Test your changes before submitting a pull request.

For example:

```sh
build/clit -h
build/clit -v
build/clit mkcd test
build/clit crun test.c
build/clit nfile -f test.txt
```

If your change affects an existing command, test both normal and invalid usage.

## Pull Requests

Push your branch:

```sh
git push -u origin your-branch-name
```

Then open a pull request on GitHub.

Your pull request should include:

* A clear title
* A short description of the changes
* Testing performed
* Any platform-specific considerations

Please keep pull requests focused and easy to review.

## Issues

When reporting a bug, include:

* Operating system
* Compiler and version
* CLIT version
* Command that caused the problem
* Expected behavior
* Actual behavior
* Relevant error output

Feature requests should explain the problem the feature would solve rather than only describing the feature itself.

## Code Style

Keep the code simple and readable.

Avoid unnecessary complexity and dependencies.

Follow the existing style of the project when modifying code.

## License

By contributing to CLIT, you agree that your contributions will be licensed under the MIT License.
