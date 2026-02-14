# Docker Configuration

Multi-stage Dockerfile for building and running the build systems demo.

## Building

```bash
# Build from repository root
docker build -f docker/Dockerfile -t build-systems:latest .

# Run container
docker run -p 3000:3000 build-systems:latest
```

## Features

- Multi-stage build for optimized image size
- Builds both Node.js and C++ components
- Production-ready configuration
- Minimal runtime dependencies

## Image Details

- Base: node:20-alpine
- Build tools: gcc:13 for C++, Node.js 20 for TypeScript
- Exposed port: 3000
