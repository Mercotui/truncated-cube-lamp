import { Server, Model } from 'miragejs'

export function makeServer({ environment = "development" } = {}) {

let server = new Server({
  environment,

  models: {
    scripts: Model,
    script_contents: Model,
  },

  seeds(server) {
    var image_val = "Y2xhc3MgQW5pbWF0aW9uIHsKICAjY29sb3IgPSAnIzA5MDkwOSc7CiAgI3ggPSAwOwogICN5ID0gMDsKCiAgdXBkYXRlIChjdHgpIHsKICAgIGN0eC5zY3JlZW4uc2V0UGl4ZWwodGhpcy4jeCwgdGhpcy4jeSwgdGhpcy4jY29sb3IpOwogICAgY3R4LnNjcmVlbi5zZXRQaXhlbCgwLCAwLCAncmVkJyk7CiAgICBjdHguc2NyZWVuLnNldFBpeGVsKDIsIDUsICdncmVlbicpOwogICAgY3R4LnNjcmVlbi5zZXRQaXhlbCg2LCA2LCAnYmx1ZScpOwogICAgY3R4LnNjcmVlbi5kcmF3KCk7CgogICAgdGhpcy4jeCsrOwogICAgaWYgKHRoaXMuI3ggPT09IDgpewogICAgICB0aGlzLiN4ID0gMDsKICAgICAgdGhpcy4jeSsrOwogICAgfQogICAgaWYgKHRoaXMuI3kgPT09IDgpIHsKICAgICAgdGhpcy4jeSA9IDA7CiAgICAgIGlmICh0aGlzLiNjb2xvciA9PT0gJyMwOTA5MDknKSB7CiAgICAgICAgdGhpcy4jY29sb3IgPSAnYmxhY2snOwogICAgICB9IGVsc2UgewogICAgICAgIHRoaXMuI2NvbG9yID0gJyMwOTA5MDknOwogICAgICB9CiAgICB9CgogICAgdmFyIG5leHQgPSBjdHguY3VycmVudF9mcmFtZV90aW1lOwogICAgbmV4dC5zZXRNaWxsaXNlY29uZHMobmV4dC5nZXRNaWxsaXNlY29uZHMoKSArIDEwMCk7CiAgICByZXR1cm4gbmV4dDsKICB9Cn0K"

    var script_val = "Y2xhc3MgQW5pbWF0aW9uIHsKICAjY29sb3IgPSAnIzA5MDkwOSc7CiAgI3ggPSAwOwogICN5ID0gMDsKCiAgdXBkYXRlIChjdHgpIHsKICAgIGN0eC5zY3JlZW4uc2V0UGl4ZWwodGhpcy4jeCwgdGhpcy4jeSwgdGhpcy4jY29sb3IpOwogICAgY3R4LnNjcmVlbi5zZXRQaXhlbCgwLCAwLCAncmVkJyk7CiAgICBjdHguc2NyZWVuLnNldFBpeGVsKDIsIDUsICdncmVlbicpOwogICAgY3R4LnNjcmVlbi5zZXRQaXhlbCg2LCA2LCAnYmx1ZScpOwogICAgY3R4LnNjcmVlbi5kcmF3KCk7CgogICAgdGhpcy4jeCsrOwogICAgaWYgKHRoaXMuI3ggPT09IDgpewogICAgICB0aGlzLiN4ID0gMDsKICAgICAgdGhpcy4jeSsrOwogICAgfQogICAgaWYgKHRoaXMuI3kgPT09IDgpIHsKICAgICAgdGhpcy4jeSA9IDA7CiAgICAgIGlmICh0aGlzLiNjb2xvciA9PT0gJyMwOTA5MDknKSB7CiAgICAgICAgdGhpcy4jY29sb3IgPSAnYmxhY2snOwogICAgICB9IGVsc2UgewogICAgICAgIHRoaXMuI2NvbG9yID0gJyMwOTA5MDknOwogICAgICB9CiAgICB9CgogICAgdmFyIG5leHQgPSBjdHguY3VycmVudF9mcmFtZV90aW1lOwogICAgbmV4dC5zZXRNaWxsaXNlY29uZHMobmV4dC5nZXRNaWxsaXNlY29uZHMoKSArIDEwMCk7CiAgICByZXR1cm4gbmV4dDsKICB9Cn0K"

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
