# Design Rationale — Composite Hierarchy (Person A)

## Why Composite fits Meridian Records

Meridian Records naturally organises work as a nested part-whole structure:
a label contains multiple artist projects, each project contains multiple
recording sessions, and each session contains multiple tracks. Reporting
tasks in this domain — for example, "what is the total production cost of
this label?" — need to aggregate over every level of this nesting without
the caller needing to know how deep the structure goes or how many items
exist at each level.

Composite solves this directly: `WorkComponent` defines one interface shared
by both the single item (`Track`) and every level of grouping (`RecordingSession`,
`ArtistProject`, `RecordLabel`). A call to `getTotalCost()` on the root
`RecordLabel` recurses transparently through every project, session, and
track beneath it, without any type-checking or special-casing of which kind
of node is being visited. This satisfies Rule 8 (no giant switch/if-else
chains standing in for the pattern) and keeps `main.cpp` decoupled from the
concrete shape of the hierarchy.

An alternative considered was giving `RecordLabel` and `ArtistProject`
separate, non-uniform interfaces from `Track` (e.g. a `getAggregateCost()`
method only on composites). This was rejected because it reintroduces the
exact type-checking problem Composite exists to avoid — client code would
need to ask "is this a leaf or a composite?" before knowing which method to
call.

## Ownership and destruction policy

Every composite (`RecordLabel`, `ArtistProject`, `RecordingSession`) owns the
`WorkComponent*` children it holds in its private container. Each composite's
destructor iterates over its children and calls `delete` on each one. Because
this is recursive by construction (a composite's children may themselves be
composites with their own destructors), deleting the root `RecordLabel`
triggers a full cascade: every `ArtistProject`, every `RecordingSession`, and
every `Track` beneath it is destroyed automatically.

This was chosen over alternatives such as shared ownership (e.g.
`shared_ptr`) or caller-managed lifetimes for two reasons:

1. **Simplicity of reasoning.** A single, consistent rule — "the parent owns
   and deletes its children" — is straightforward to verify by inspection
   and holds at every level of the hierarchy without exception.
2. **Matches the domain.** A `Track` genuinely has no independent existence
   outside the `RecordingSession` it was recorded in; deleting the session
   should reasonably delete its tracks too. There is no use case in this
   domain for a track to outlive the session that owns it.

`WorkComponent` declares a virtual destructor, satisfying Rule 4, so deleting
through a base-class pointer (e.g. `WorkComponent* root = label; delete root;`)
correctly invokes each derived class's destructor rather than only the base
class's.

## Satisfying Rule 7 (no container exposure)

The `children` container in every composite is declared `private`. Client
code (`main.cpp`) has no way to obtain it directly. All traversal is done
through `createIterator()`, which returns an `Iterator*` exposing only
`hasNext()`/`next()` — the concrete storage mechanism (`std::vector`) is never
visible outside the composite class that owns it.
