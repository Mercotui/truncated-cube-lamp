module.exports = {
  root: true,
  env: {
    node: true,
  },
  globals: {
    definePage: "readonly",
  },
  extends: [
    'plugin:vue/vue3-essential',
    'eslint:recommended',
  ],
}
