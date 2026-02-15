# Contributing to Build Systems Demo

Thank you for your interest in contributing!

## Development Process

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Make your changes
4. Run tests and linting
5. Commit your changes using semantic commit messages (see below)
6. Push to the branch (`git push origin feature/amazing-feature`)
7. Open a Pull Request

## Commit Message Convention

This project follows [Conventional Commits](https://www.conventionalcommits.org/) for semantic versioning.

### Format

```
<type>(<scope>): <subject>

<body>

<footer>
```

### Types

- `feat`: A new feature
- `fix`: A bug fix
- `docs`: Documentation changes
- `style`: Code style changes (formatting, missing semi-colons, etc.)
- `refactor`: Code refactoring without changing functionality
- `perf`: Performance improvements
- `test`: Adding or updating tests
- `build`: Changes to build system or dependencies
- `ci`: Changes to CI configuration
- `chore`: Other changes that don't modify src or test files

### Examples

```bash
# Feature
git commit -m "feat(web): add user authentication endpoint"

# Bug fix
git commit -m "fix(native): handle division by zero in calculator"

# Documentation
git commit -m "docs(readme): update installation instructions"

# Breaking change
git commit -m "feat(api)!: change response format to JSON-API spec

BREAKING CHANGE: API responses now follow JSON-API specification"
```

### Scope

Scope can be one of: `web`, `native`, `android`, `docker`, `infra`, `ci`, `docs`

## Code Standards

### TypeScript/JavaScript
- Follow ESLint configuration
- Use TypeScript strict mode
- Write meaningful variable names
- Add comments for complex logic

### C++
- Follow C++17 standards
- Use consistent naming conventions
- Document public APIs
- Write testable code

### Android
- Follow Android best practices
- Use Material Design guidelines
- Optimize for performance
- Test on multiple device sizes

## Testing

All code changes should include tests:
- Web: Jest tests for new functionality
- Native: CTest for library functions
- Android: JUnit tests for components

## Documentation

- Update README.md for user-facing changes
- Update CHANGELOG.md with your changes
- Add inline comments for complex code
- Document new APIs and features

## Pull Request Process

1. Ensure all tests pass
2. Update documentation
3. Add changelog entry
4. Follow semantic commit convention
5. Request review from maintainers
6. Address review feedback
7. Squash commits if requested

## Semantic Release

This project uses automated semantic releases. When your PR is merged to `main`:

1. Commits are analyzed for type (`feat`, `fix`, etc.)
2. Version is automatically bumped based on commit types
3. CHANGELOG is auto-generated
4. Release is created with artifacts
5. Docker images are published

## Branch Protection

The `main` branch is protected and requires:
- All CI checks to pass
- At least one approval from a code owner
- Commits to follow semantic commit convention
- No force pushes

## Questions?

Open an issue for questions or discussions.
