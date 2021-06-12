import { Server, Model } from 'miragejs'

export function makeServer({ environment = "development" } = {}) {

let server = new Server({
  environment,

  models: {
    scripts: Model,
    script_contents: Model,
  },

  seeds(server) {
    var image_val = "KGZ1bmN0aW9uIChwYXJhbXMpIHsKICAgIHNjcmVlbi5zZXRQaXhlbCh4LCB5LCBjb2xvcik7CiAgICBzY3JlZW4uc2V0UGl4ZWwoMCwgMCwgJ3JlZCcpOwogICAgc2NyZWVuLnNldFBpeGVsKDIsIDUsICdncmVlbicpOwogICAgc2NyZWVuLnNldFBpeGVsKDYsIDYsICdibHVlJyk7CiAgICBzY3JlZW4uZHJhdygpOwoKICAgIHgrKwogICAgaWYgKHggPT09IDgpewogICAgICB4ID0gMAogICAgICB5KysKICAgIH0KICAgIGlmICh5ID09PSA4KSB7CiAgICAgIHkgPSAwCiAgICAgIGlmIChjb2xvciA9PT0gJyMwOTA5MDknKSB7CiAgICAgICAgY29sb3IgPSAnYmxhY2snCiAgICAgIH0gZWxzZSB7CiAgICAgICAgY29sb3IgPSAnIzA5MDkwOScKICAgICAgfQogICAgfQoKICAgIHZhciBuZXh0ID0gcGFyYW1zLmN1cnJlbnRfZnJhbWVfdGltZTsKICAgIG5leHQuc2V0TWlsbGlzZWNvbmRzKG5leHQuZ2V0TWlsbGlzZWNvbmRzKCkgKyAxMDApOwogICAgcmV0dXJuIG5leHQ7Cn0pCnZhciBjb2xvciA9ICcjMDkwOTA5Jwp2YXIgeCA9IDAKdmFyIHkgPSAwCg=="

    var script_val = "KGZ1bmN0aW9uIChwYXJhbXMpIHsKICAgIHNjcmVlbi5zZXRQaXhlbCh4LCB5LCBjb2xvcik7CiAgICBzY3JlZW4uc2V0UGl4ZWwoMCwgMCwgJ3JlZCcpOwogICAgc2NyZWVuLnNldFBpeGVsKDIsIDUsICdncmVlbicpOwogICAgc2NyZWVuLnNldFBpeGVsKDYsIDYsICdibHVlJyk7CiAgICBzY3JlZW4uZHJhdygpOwoKICAgIHgrKwogICAgaWYgKHggPT09IDgpewogICAgICB4ID0gMAogICAgICB5KysKICAgIH0KICAgIGlmICh5ID09PSA4KSB7CiAgICAgIHkgPSAwCiAgICAgIGlmIChjb2xvciA9PT0gJyMwOTA5MDknKSB7CiAgICAgICAgY29sb3IgPSAnYmxhY2snCiAgICAgIH0gZWxzZSB7CiAgICAgICAgY29sb3IgPSAnIzA5MDkwOScKICAgICAgfQogICAgfQoKICAgIHZhciBuZXh0ID0gcGFyYW1zLmN1cnJlbnRfZnJhbWVfdGltZTsKICAgIG5leHQuc2V0TWlsbGlzZWNvbmRzKG5leHQuZ2V0TWlsbGlzZWNvbmRzKCkgKyAxMDApOwogICAgcmV0dXJuIG5leHQ7Cn0pCnZhciBjb2xvciA9ICcjMDkwOTA5Jwp2YXIgeCA9IDAKdmFyIHkgPSAwCg=="

    server.create("script", { name: "first-test", type: ["animation"], script: script_val })
    server.create("script", { name: "second-dummy", type: ["animation"], script: script_val })
    server.create("script", { name: "a-default-test", type: ["animation", "default"], script: script_val })
    server.create("script", { name: "first-image", type: ["image"], script: image_val })
    server.create("script", { name: "second-image", type: ["image"], script: image_val })
    server.create("script", { name: "a-default-image", type: ["image", "default"], script: image_val })
  },

  routes() {
    this.namespace = "api"

    this.get("/scripts/", schema => {
      return schema.scripts.all()
    })

    this.get("/scripts/:name", (schema, request) => {
      return schema.scripts.findBy({name: request.params.name}).attrs
    })

    this.put("/scripts/:name", () => {})

    this.delete("/scripts/:name", () => {})
  },
  })

  return server
}
