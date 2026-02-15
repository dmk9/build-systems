# Multi-stage build for web application
FROM node:20-alpine AS web-builder

WORKDIR /app/web
COPY web/package*.json ./
RUN npm ci
COPY web/ ./
RUN npm run build

# C++ builder stage
FROM gcc:13 AS native-builder

WORKDIR /app/native
RUN apt-get update && apt-get install -y cmake
COPY native/ ./
RUN mkdir build && cd build && \
    cmake .. && \
    cmake --build .

# Final runtime image
FROM node:20-alpine

WORKDIR /app

# Copy built artifacts
COPY --from=web-builder /app/web/dist ./web/dist
COPY --from=web-builder /app/web/package*.json ./web/
COPY --from=native-builder /app/native/build/demo ./native/demo

# Install production dependencies
WORKDIR /app/web
RUN npm ci --only=production

EXPOSE 3000

CMD ["npm", "start"]
