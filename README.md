# TaskForge — Hierarchical Work Processing (Meridian Records)

COS 214 Practical 4 — Group submission.

## Team

| Member | Role |
|---|---|
| Person A | Composite hierarchy, Docker/build, design lead |
| Person B | State + Decorator |
| Person C | Iterator, main.cpp scenarios, debugging, packaging |

## System Description

<!-- TODO (all members, ~2-3 sentences): brief description of the Meridian Records
domain and what problem TaskForge solves. -->

## Build and Run (Docker)

This project is designed to be built and run entirely inside the supplied Docker
container, which includes g++, make, gdb, and valgrind — no local installation
of these tools is required.

### 1. Build the Docker image

```bash
docker build -t taskforge .
```

### 2. Run the program

```bash
docker run -it taskforge
```

This builds `taskforge` automatically as part of the image build (via `make`,
using the project Makefile) and runs it as the container's default command.

### 3. Build/run manually inside the container (for debugging)

If you want an interactive shell inside the container instead of running
`taskforge` immediately:

```bash
docker run -it --entrypoint /bin/bash taskforge
make            # rebuild manually if needed
./taskforge      # run the program
```

### 4. Building without Docker (optional, for local development)

If g++ (supporting C++11), make, gdb, and valgrind are already installed
locally, the project can also be built directly:

```bash
make
./taskforge
```

Run `make clean` to remove the built binary.

## Debugging Inside the Container

### GDB

```bash
docker run -it --entrypoint /bin/bash taskforge
gdb ./taskforge
```

<!-- TODO (Person C): add the specific breakpoints/commands used for the
GDB investigation, matching what's written up in the PDF. -->

### Valgrind

```bash
docker run -it --entrypoint /bin/bash taskforge
valgrind --leak-check=full --show-leak-kinds=all ./taskforge
```

## Project Structure

```
taskforge/
├── include/         # header files
├── src/             # .cpp source files, including main.cpp
├── docs/            # design documents / exported UML diagrams
├── Makefile
├── Dockerfile
└── README.md
```

## Composite Hierarchy (Person A)

`WorkComponent` is the shared abstract interface (`getName()`, `getTotalDuration()`,
`getTotalCost()`, `createIterator()`) implemented by both the leaf and every
composite, so client code can treat a single track and an entire nested label
identically. The hierarchy is `RecordLabel -> ArtistProject -> RecordingSession
-> Track`, satisfying the 3-levels-of-nesting-below-root requirement. Each
composite holds its children in a private `vector<WorkComponent*>` and never
exposes it directly; all traversal goes through `createIterator()`. Ownership
policy: every composite owns its children and deletes them in its destructor,
so destroying the root `RecordLabel` recursively cleans up the entire tree.

## State and Decorator (Person B)

<!-- TODO (Person B): 2-3 sentences on the Track lifecycle (states used,
how invalid transitions are handled) and the Decorator responsibilities
implemented (list the 4 concrete decorators), including how stacking works. -->

## Iterator and Dynamic Scenarios (Person C)

<!-- TODO (Person C): 2-3 sentences on FullCatalogIterator vs
PendingStageIterator, and a one-line summary of the team's traversal-
modification policy (snapshot / live / invalidation) decided together. -->

## Known Issues / Debugging Notes

<!-- TODO (Person C): summary of the genuine bug found during development
(symptom, cause, fix) - full writeup goes in the submitted PDF, this can
just be a one-line pointer. -->

<!-- TODO (Person C): summary of the genuine bug found during development
(symptom, cause, fix) - full writeup goes in the submitted PDF, this can
just be a one-line pointer. -->
