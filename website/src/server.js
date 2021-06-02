import { Server, Model } from 'miragejs'

export function makeServer({ environment = "development" } = {}) {

let server = new Server({
  environment,

  models: {
    scripts: Model,
  },

  seeds(server) {
    server.create("script", { name: "first test", type: ["animation"] })
    server.create("script", { name: "second dummy", type: ["animation"] })
    server.create("script", { name: "third dummy", type: ["animation"] })
    server.create("script", { name: "fourth dummy", type: ["animation"] })
    server.create("script", { name: "a default test", type: ["animation", "default"] })
  },

  routes() {
    this.namespace = "api"

    this.get("/scripts/", schema => {
      return schema.scripts.all()
    })
  },
  })

  return server
}
