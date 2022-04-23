# Building the buildenv container

To build a new version of the buildenv container, ensure login on the github container registry:

```bash
podman login --username mercotui --password <Personal Access Token> ghcr.io
```

Then to build, tag, and push:

```bash
podman build -f Containerfile.buildenv -t ghcr.io/mercotui/truncated_buildenv:latest .
podman push ghcr.io/mercotui/truncated_buildenv:latest
```
