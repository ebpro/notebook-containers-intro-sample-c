# Introduction to Docker Containers with a C Application

This example demonstrates how to package a simple C application into a Docker container.

The repository contains:

* `helloworld.c` — a simple application displaying information about its execution environment.
* `Dockerfile.single` — a single-stage build.
* `Dockerfile.multistage` — a multi-stage build.

## Learning Objectives

After completing this example, you should be able to:

* Build a Docker image.
* Run a container.
* Understand the purpose of `FROM`, `COPY`, `RUN`, `WORKDIR`, `USER`, `CMD`, and `ENTRYPOINT`.
* Compare single-stage and multi-stage builds.
* Explain why multi-stage builds produce smaller runtime images.

# The Application

The program prints information about its execution environment:

* Container hostname
* Process identifier (PID)
* User identifier (UID)
* An optional environment variable (`NAME`)

Example output:

```text
Hostname : 8c43b0a0d77b
PID      : 1
UID      : 999
Hello World!
```

# Single-Stage Build

Build the image:

```bash
docker build \
    -f Dockerfile.single \
    -t hello:single .
```

Run the container:

```bash
docker run --rm hello:single
```

Override the environment variable:

```bash
docker run --rm \
    -e NAME=Alice \
    hello:single
```

Example output:

```text
Hostname : 8c43b0a0d77b
PID      : 1
UID      : 999
Hello Alice!
```

# Multi-Stage Build

Build the image:

```bash
docker build \
    -f Dockerfile.multistage \
    -t hello:multi .
```

Run the container:

```bash
docker run --rm hello:multi
```

The application behaves exactly the same, but the runtime image contains only the executable and the required runtime components.

# Compare the Images

List the images:

```bash
docker images hello
```

or

```bash
docker image ls
```

Notice that the multi-stage image is significantly smaller because it does not include the compiler and development tools.

You can also inspect the image layers:

```bash
docker history hello:single
```

```bash
docker history hello:multi
```

# Experiments

Try the following commands.

## Change the greeting

```bash
docker run --rm \
    -e NAME=Docker \
    hello:multi
```

## Change the hostname

```bash
docker run --rm \
    --hostname=my-container \
    hello:multi
```

## Observe the running user

The Dockerfile creates a non-root user.

Verify the displayed UID and compare it with an image running as the root user.
