# Docker Configuration

This directory contains Docker configuration for the build-systems multi-platform demo.

## Files

- `Dockerfile` - Multi-stage build for web and native components
- `docker-compose.yml` - Orchestration configuration

## Container Registry: GitHub Container Registry (GHCR)

GHCR is configured as the default container registry.

**Benefits:**
- No additional secrets required
- Uses `GITHUB_TOKEN` automatically in GitHub Actions
- Integrated with GitHub Security features
- Free for public repositories

**Pull the image:**
```bash
# Latest release
docker pull ghcr.io/dmk9/build-systems:latest

# Specific version
docker pull ghcr.io/dmk9/build-systems:v1.0.0

# Run container
docker run -p 3000:3000 ghcr.io/dmk9/build-systems:latest
```

## Alternative: Docker Hub

To use Docker Hub instead of GHCR:

**Required Secrets:**
- `DOCKER_USERNAME` - Your Docker Hub username  
- `DOCKER_PASSWORD` - Docker Hub access token

**Update `.github/workflows/release.yml`:**
```yaml
- name: Log in to Docker Hub
  uses: docker/login-action@v3
  with:
    username: ${{ secrets.DOCKER_USERNAME }}
    password: ${{ secrets.DOCKER_PASSWORD }}
```

## Building Locally

```bash
# Standard build
docker build -f docker/Dockerfile -t build-systems:local .

# Run locally
docker run -p 3000:3000 build-systems:local

# Multi-arch build (requires buildx)
docker buildx build --platform linux/amd64,linux/arm64 \
  -f docker/Dockerfile -t build-systems:multi-arch .
```

## Security Scanning

Automatic Trivy scanning runs on every release:
- Scans for vulnerabilities
- Reports to GitHub Security tab

**Manual scan:**
```bash
docker run --rm -v /var/run/docker.sock:/var/run/docker.sock \
  aquasec/trivy image ghcr.io/dmk9/build-systems:latest
```

## Image Details

- **Base Images**: node:20-alpine, gcc:13
- **Multi-stage**: Optimized for size
- **Platforms**: linux/amd64, linux/arm64
- **Port**: 3000

## Secrets Configuration

### GHCR (Default)
No setup required! Uses automatic `GITHUB_TOKEN`.

### Docker Hub (Optional)
Add to repository secrets:
1. Settings → Secrets and variables → Actions
2. Add `DOCKER_USERNAME` and `DOCKER_PASSWORD`

## References

- [GHCR Documentation](https://docs.github.com/packages/working-with-a-github-packages-registry/working-with-the-container-registry)
- [Trivy Scanner](https://github.com/aquasecurity/trivy)
