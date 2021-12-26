# website

## Project setup

For node>16 use:
```bash
export NODE_OPTIONS=--openssl-legacy-provider
```

Then use:

```bash
npm install
npm run serve
npm run build
npm run package
npm run lint
```

### Customize configuration

See [Configuration Reference](https://cli.vuejs.org/config/).

## Deploying to other systems

It might be useful to build on one system and compile on another, after building:

```bash
rsync dist/ user@remote:~/truncated-cube-lamp/website/dist --recursive --delete
```
