# Multi-Platform Build Systems Demo

A comprehensive demonstration of modern build and release automation across multiple platforms and technologies.

[![CI Pipeline](https://github.com/dmk9/build-systems/workflows/CI%20Pipeline/badge.svg)](https://github.com/dmk9/build-systems/actions/workflows/ci.yml)
[![Android CI](https://github.com/dmk9/build-systems/workflows/Android%20CI/badge.svg)](https://github.com/dmk9/build-systems/actions/workflows/android.yml)
[![Infrastructure](https://github.com/dmk9/build-systems/workflows/Infrastructure/badge.svg)](https://github.com/dmk9/build-systems/actions/workflows/infra.yml)
[![CodeQL](https://github.com/dmk9/build-systems/workflows/CodeQL%20Security%20Analysis/badge.svg)](https://github.com/dmk9/build-systems/actions/workflows/codeql.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Docker](https://img.shields.io/badge/Docker-GHCR-blue)](https://github.com/dmk9/build-systems/pkgs/container/build-systems)

## Overview

This repository showcases expertise in:
- **GitHub Actions** - Automated CI/CD pipelines
- **Docker** - Multi-stage containerization
- **C++ with CMake** - Native library development
- **Node.js/TypeScript** - Modern web applications
- **Android CI** - Mobile application builds
- **Release Automation** - Automated versioning and deployment
- **Infrastructure as Code** - Terraform for AWS

## Project Structure

```
repo/
├── web/                    # Node.js/TypeScript web application
│   ├── src/               # Source code
│   ├── package.json       # NPM configuration
│   └── tsconfig.json      # TypeScript configuration
├── native/                # C++ library with CMake
│   ├── include/          # Header files
│   ├── src/              # Source files
│   └── CMakeLists.txt    # CMake configuration
├── mobile/
│   └── android/          # Android sample application
│       ├── app/          # Application code
│       └── build.gradle  # Gradle build configuration
├── docker/               # Docker configuration
│   ├── Dockerfile        # Multi-stage build
│   └── docker-compose.yml
├── infra/
│   └── terraform/        # Infrastructure as Code
│       ├── main.tf       # Main configuration
│       ├── variables.tf  # Variable definitions
│       └── resources.tf  # AWS resources
├── .github/workflows/    # CI/CD pipelines
    ├── ci.yml           # Continuous Integration
    ├── android.yml      # Android builds
    ├── release.yml      # Release automation
    ├── infra.yml        # Infrastructure validation
    └── codeql.yml       # Security analysis
```

## Quick Start

### Web Application

```bash
cd web
npm install
npm run build
npm start
```

Access at http://localhost:3000

### Native C++ Library

```bash
cd native
mkdir build && cd build
cmake ..
cmake --build .
./demo
```

### Android Application

```bash
cd mobile/android
./gradlew assembleDebug
./gradlew installDebug
```

### Docker

```bash
# Build and run with Docker
docker build -f docker/Dockerfile -t build-systems:latest .
docker run -p 3000:3000 build-systems:latest

# Pull from GitHub Container Registry
docker pull ghcr.io/dmk9/build-systems:latest
docker run -p 3000:3000 ghcr.io/dmk9/build-systems:latest

# Or use docker-compose
cd docker
docker-compose up
```

### Infrastructure

```bash
cd infra/terraform
terraform init
terraform plan
terraform apply
```

## CI/CD Pipelines

### Continuous Integration (ci.yml)

Runs on every push and pull request:
- Builds web application (TypeScript compilation, linting, testing)
- Builds native library (C++ with CMake, CTest)
- Builds Docker image with multi-arch support
- Security scanning (npm audit)
- **Caching**: npm dependencies, ccache for C++ builds

### Android CI (android.yml)

Triggered by changes to Android code:
- Builds debug and release APKs
- Runs unit tests
- Uploads build artifacts
- **Caching**: Gradle dependencies and wrapper

### Infrastructure (infra.yml)

Validates Terraform configurations:
- Format checking
- Initialization
- Validation
- Uploads validated configuration

### CodeQL Security Analysis (codeql.yml)

Runs security analysis on:
- JavaScript/TypeScript code
- C++ code
- Java (Android) code
- Scheduled weekly scans

### Release Pipeline (release.yml)

Triggered by version tags:
- **Requires**: All CI tests pass
- Creates GitHub release
- Builds and archives all components
- Pushes Docker images to GHCR
- Multi-architecture support (amd64, arm64)
- Attaches release artifacts

## Components

### Web Application

- **Technology**: Node.js 20, TypeScript 5, Express.js
- **Build**: TypeScript compiler
- **Testing**: Jest
- **Linting**: ESLint

### Native Library

- **Technology**: C++17, CMake 3.15+
- **Features**: Simple calculator library
- **Testing**: CTest
- **Build**: Multi-platform support

### Android Application

- **Technology**: Android SDK 34, Java 11
- **Build**: Gradle 8.2
- **UI**: Material Design
- **Testing**: JUnit

### Docker

- **Base Images**: node:20-alpine, gcc:13
- **Build**: Multi-stage for optimization
- **Size**: Minimal runtime dependencies

### Infrastructure

- **Provider**: AWS
- **Resources**: VPC, Subnets, ECR
- **State**: S3 backend support
- **Modules**: Reusable infrastructure components
- **Security**: No credentials committed, uses environment variables

## Development

### Prerequisites

- Node.js 20+
- CMake 3.15+
- GCC 11+ or MSVC 2019+
- Android SDK 34 (for mobile builds)
- Docker (for containerization)
- Terraform 1.0+ (for infrastructure)

### Building All Components

```bash
# Web
cd web && npm ci && npm run build && cd ..

# Native
cd native && mkdir -p build && cd build && cmake .. && cmake --build . && cd ../..

# Docker
docker build -f docker/Dockerfile -t build-systems:latest .
```

### Running Tests

```bash
# Web tests
cd web && npm test

# Native tests
cd native/build && ctest

# Android tests
cd mobile/android && ./gradlew test
```

## Deployment

### Docker Image from GHCR

```bash
# Pull latest release
docker pull ghcr.io/dmk9/build-systems:latest

# Pull specific version
docker pull ghcr.io/dmk9/build-systems:v1.0.0

# Run container
docker run -p 3000:3000 ghcr.io/dmk9/build-systems:latest
```

### Automated Deployment

Create a new release:

```bash
git tag -a v1.0.0 -m "Release version 1.0.0"
git push origin v1.0.0
```

This triggers the release pipeline which:
- Runs full CI test suite
- Creates a GitHub release
- Builds all components
- Publishes multi-arch Docker images to GHCR
- Attaches release artifacts

See [RELEASE.md](RELEASE.md) for detailed release process.

## Infrastructure

### AWS Resources

The Terraform configuration creates:
- VPC with public subnets across 2 AZs
- Internet Gateway and route tables
- ECR repository for Docker images
- Lifecycle policies for image management

### Deploying Infrastructure

```bash
cd infra/terraform

# Configure backend (optional)
export TF_STATE_BUCKET="my-terraform-state-bucket"

# Initialize
terraform init

# Plan with backend config
terraform plan

# Apply
terraform apply
```

### Infrastructure Outputs

- `vpc_id` - VPC identifier
- `public_subnet_ids` - List of subnet IDs
- `ecr_repository_url` - Docker registry URL

## Security Features

- **CodeQL Analysis**: Automated security scanning for JavaScript, C++, and Java
- **Dependabot**: Automated dependency updates across all ecosystems
- **npm audit**: Security scanning in CI pipeline
- **Trivy**: Container vulnerability scanning for Docker images
- **Secret Management**: No credentials committed, using GitHub Secrets
- **Least Privilege**: Minimal permissions for GitHub Actions
- **Multi-arch Images**: Support for amd64 and arm64 platforms

## Architecture & Pipeline Flow

### CI/CD Pipeline Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                     Developer Workflow                        │
├─────────────────────────────────────────────────────────────┤
│ 1. Code Push → GitHub                                        │
│ 2. CI Triggers (web, native, docker, android, infra)        │
│ 3. Parallel Builds with Caching                             │
│ 4. Security Scans (CodeQL, npm audit, Trivy)                │
│ 5. Artifact Upload                                           │
└─────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────┐
│                    Release Workflow                          │
├─────────────────────────────────────────────────────────────┤
│ Trigger: Tag push (v*)                                       │
│ 1. Create GitHub Release                                     │
│ 2. Build Web + Native (with cache)                          │
│ 3. Build Multi-arch Docker (amd64, arm64)                   │
│ 4. Trivy Security Scan                                       │
│ 5. Push to GHCR                                             │
│ 6. Upload Release Artifacts                                  │
└─────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────┐
│                    Deployment Targets                         │
├─────────────────────────────────────────────────────────────┤
│ • GHCR: ghcr.io/dmk9/build-systems:latest                   │
│ • GitHub Releases: Downloadable artifacts                    │
│ • Multi-platform: linux/amd64, linux/arm64                   │
└─────────────────────────────────────────────────────────────┘
```

### Observability & Monitoring

#### Health Checks

The web application provides health endpoints:
- `GET /` - Main API with system information
- `GET /health` - Health check endpoint (returns 200 OK)

#### Metrics to Monitor

For production deployments, monitor these key metrics:

| Metric | Alert Threshold | Action |
|--------|----------------|--------|
| **Error Rate** | > 1% over 5 min | Page on-call team |
| **Response Time (p95)** | > 500ms | Warning alert |
| **Container Restarts** | > 3 in 10 min | Page on-call team |
| **Failed Health Checks** | > 2 consecutive | Trigger alert |
| **CPU Usage** | > 80% for 5 min | Scale up |
| **Memory Usage** | > 85% | Scale up or investigate leak |

#### Rollback Strategy

**Automated Rollback Triggers:**
1. **Error rate spike**: > 5% errors for 2 minutes
2. **Health check failures**: 3 consecutive failures
3. **Crash loop**: Container restarts > 5 times in 5 minutes

**Manual Rollback Process:**
```bash
# Identify last stable version
kubectl rollout history deployment/build-systems

# Rollback to previous version
kubectl rollout undo deployment/build-systems

# Or rollback to specific version
kubectl rollout undo deployment/build-systems --to-revision=2

# For Docker deployment
docker pull ghcr.io/dmk9/build-systems:v1.0.0  # previous version
docker stop current-container
docker run -d -p 3000:3000 ghcr.io/dmk9/build-systems:v1.0.0
```

**Rollback Validation:**
1. Verify health checks pass
2. Check error rates return to baseline
3. Monitor for 15 minutes
4. Create incident report

#### Logging

**Application Logs:**
- Structured JSON logging (recommended for production)
- Log levels: ERROR, WARN, INFO, DEBUG
- Include request IDs for tracing

**Container Logs:**
```bash
# View logs
docker logs -f <container-id>

# Export logs
docker logs <container-id> > app.log 2>&1
```

**Log Aggregation (Production):**
- Use ELK stack (Elasticsearch, Logstash, Kibana)
- Or CloudWatch Logs for AWS deployments
- Or Google Cloud Logging for GCP

#### Alerting Configuration

**Alert Routing:**
- **Critical**: Page on-call (PagerDuty/Opsgenie)
- **Warning**: Slack channel notification
- **Info**: Email to team

**Example Prometheus Alert:**
```yaml
- alert: HighErrorRate
  expr: rate(http_requests_total{status=~"5.."}[5m]) > 0.01
  for: 2m
  labels:
    severity: critical
  annotations:
    summary: "High error rate detected"
    description: "Error rate is {{ $value }} (>1%)"
```

### Required Status Checks

For branch protection, configure these as required checks:

- ✅ `CI Pipeline / web-build`
- ✅ `CI Pipeline / native-build`
- ✅ `CI Pipeline / docker-build`
- ✅ `CI Pipeline / security-scan`
- ✅ `CodeQL Security Analysis`
- ✅ `Infrastructure / terraform-validate`

See `.github/CODEOWNERS` for code review requirements.

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Run tests and linting
5. Submit a pull request

## License

MIT License - see LICENSE file for details

## Contact

For questions or issues, please open a GitHub issue.