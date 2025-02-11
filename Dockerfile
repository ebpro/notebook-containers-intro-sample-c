# Build stage
FROM gcc:14-bookworm AS builder

# An argument sets at build command with --build-arg
# It as a default value
ARG BUILD_DATE=1970-01-01T00:00:00Z

# key-value pair as image metadata
LABEL maintainer="emmanuel.bruno@univ-tln.fr"
# See http://label-schema.org/rc1/ for a list of usefull labels
LABEL org.label-schema.build-date=$BUILD_DATE

WORKDIR /src/app
COPY helloworld.c .
RUN gcc -Wall -Wextra -Werror -O2 -fPIE -pie -D_FORTIFY_SOURCE=2 -static-libgcc helloworld.c -o helloworld

# Runtime stage
FROM debian:bookworm-slim

# Create non-root user
RUN groupadd -r appuser && useradd -r -g appuser appuser
WORKDIR /app

# Copy only the compiled binary
COPY --from=builder --chown=appuser:appuser /src/app/helloworld /app/helloworld

# Switch to non-root user
USER appuser

# Set executable permissions
RUN chmod 550 /app/helloworld

ENTRYPOINT ["/app/helloworld"]