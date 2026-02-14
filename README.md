# Multi-Platform Build Systems Demo

A comprehensive demonstration of modern build and release automation across multiple platforms and technologies.

[![CI Pipeline](https://github.com/dmk9/build-systems/workflows/CI%20Pipeline/badge.svg)](https://github.com/dmk9/build-systems/actions)
[![Android CI](https://github.com/dmk9/build-systems/workflows/Android%20CI/badge.svg)](https://github.com/dmk9/build-systems/actions)

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
└── .github/workflows/    # CI/CD pipelines
    ├── ci.yml           # Continuous Integration
    ├── android.yml      # Android builds
    └── release.yml      # Release automation
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
- Builds web application (TypeScript)
- Builds native library (C++ with CMake)
- Builds Docker image
- Validates Terraform configuration

### Android CI (android.yml)

Triggered by changes to Android code:
- Builds Android APK
- Runs unit tests
- Uploads build artifacts

### Release Pipeline (release.yml)

Triggered by version tags:
- Creates GitHub release
- Builds and archives all components
- Pushes Docker image to registry
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

### Manual Deployment

1. Build Docker image: `docker build -f docker/Dockerfile -t build-systems:latest .`
2. Tag image: `docker tag build-systems:latest your-registry/build-systems:v1.0.0`
3. Push image: `docker push your-registry/build-systems:v1.0.0`

### Automated Deployment

Create a new release:

```bash
git tag -a v1.0.0 -m "Release version 1.0.0"
git push origin v1.0.0
```

This triggers the release pipeline which:
- Creates a GitHub release
- Builds all components
- Publishes Docker image
- Attaches release artifacts

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
terraform init
terraform plan -out=tfplan
terraform apply tfplan
```

### Infrastructure Outputs

- `vpc_id` - VPC identifier
- `public_subnet_ids` - List of subnet IDs
- `ecr_repository_url` - Docker registry URL

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