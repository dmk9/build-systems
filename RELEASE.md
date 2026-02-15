# Release Process

This document describes the release process for the build-systems project.

## Overview

Releases are automated through GitHub Actions and follow semantic versioning (semver).

## Release Types

- **Patch Release** (v1.0.x): Bug fixes and minor updates
- **Minor Release** (v1.x.0): New features, backward compatible
- **Major Release** (vx.0.0): Breaking changes

## Creating a Release

### Automated Release (Recommended)

1. Ensure all CI checks pass on the `main` branch
2. Create and push a version tag:
   ```bash
   git tag -a v1.0.0 -m "Release version 1.0.0"
   git push origin v1.0.0
   ```
3. The release workflow automatically:
   - Runs full CI test suite
   - Builds all components (web, native, Android)
   - Creates GitHub release with artifacts
   - Publishes Docker images to GHCR (ghcr.io)
   - Generates multi-architecture images (amd64, arm64)

### Manual Release

Alternatively, trigger a release manually:
1. Go to Actions → Release Pipeline
2. Click "Run workflow"
3. Enter the version (e.g., v1.0.0)
4. Click "Run workflow"

## Release Artifacts

Each release includes:
- **Web Application**: Compiled TypeScript build (`web-v*.tar.gz`)
- **Native Library**: C++ library and demo binary (`native-v*.tar.gz`)
- **Docker Images**: Multi-arch container images on GHCR
  - `ghcr.io/dmk9/build-systems:latest`
  - `ghcr.io/dmk9/build-systems:v1.0.0`
  - `ghcr.io/dmk9/build-systems:1.0`

## Tag Naming Convention

- Format: `vMAJOR.MINOR.PATCH`
- Examples: `v1.0.0`, `v1.2.3`, `v2.0.0`
- Pre-releases: `v1.0.0-rc.1`, `v1.0.0-beta.1`

## Artifact Provenance

All release artifacts are:
- Built from tagged commits in CI
- Signed and traceable through GitHub Actions logs
- Downloadable from GitHub Releases page
- Container images signed with cosign (future enhancement)

## Docker Image Distribution

Images are pushed to GitHub Container Registry (GHCR):

```bash
# Pull latest release
docker pull ghcr.io/dmk9/build-systems:latest

# Pull specific version
docker pull ghcr.io/dmk9/build-systems:v1.0.0

# Run container
docker run -p 3000:3000 ghcr.io/dmk9/build-systems:latest
```

## Multi-Architecture Support

Docker images support:
- `linux/amd64` - Standard x86_64 systems
- `linux/arm64` - ARM-based systems (Apple Silicon, AWS Graviton, etc.)

## Rollback Procedure

If a release has issues:

1. **Immediate Rollback**:
   ```bash
   # Revert to previous Docker image
   docker pull ghcr.io/dmk9/build-systems:v1.0.0  # previous version
   ```

2. **Create Patch Release**:
   ```bash
   # Fix the issue in code
   git commit -m "fix: critical bug in release"
   git tag -a v1.0.1 -m "Hotfix release"
   git push origin v1.0.1
   ```

3. **Mark Release as Pre-release**:
   - Go to GitHub Releases
   - Edit the problematic release
   - Check "This is a pre-release"
   - Add warning in release notes

## Release Checklist

Before creating a release:

- [ ] All CI checks pass
- [ ] CHANGELOG.md updated with changes
- [ ] Version bumped in package.json (web)
- [ ] Version bumped in CMakeLists.txt (native)
- [ ] Version bumped in build.gradle (Android)
- [ ] Documentation updated
- [ ] Security scan passes (CodeQL, npm audit)
- [ ] Manual testing completed
- [ ] Breaking changes documented (if any)

## Monitoring Release Health

After release deployment:

1. **Check CI Status**: Verify release workflow completed successfully
2. **Verify Artifacts**: Download and test release artifacts
3. **Test Docker Image**: Pull and run container to verify functionality
4. **Monitor Logs**: Check application logs for errors
5. **Review Metrics**: Monitor error rates and performance (if production)

## Production Deployment Alerts

For production deployments, the following metrics trigger alerts:

- **Error Rate**: > 1% over 5 minutes → Page on-call
- **Response Time**: p95 > 500ms → Warning alert
- **Container Crashes**: > 3 restarts in 10 minutes → Page on-call
- **Failed Health Checks**: > 2 consecutive failures → Alert

## Security

- Never commit signing keys or credentials
- Use GitHub Secrets for sensitive data
- Review Dependabot alerts before releases
- Run security scans (CodeQL, npm audit)
- Keep dependencies up to date

## Support

For questions about releases:
- Open an issue on GitHub
- Check CI/CD workflow logs
- Review CONTRIBUTING.md for development guidelines
