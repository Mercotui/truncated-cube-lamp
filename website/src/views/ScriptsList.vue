<template>
  <v-container>
    <v-row class="text-center">
      <v-col class="mb-4">
        <v-list dense>
          <v-subheader>Images</v-subheader>
          <v-list-item>
            <v-list-item-content>
              <v-list-item-title>Draw</v-list-item-title>
            </v-list-item-content>
            <v-list-item-icon>
              <v-icon>mdi-brush</v-icon>
            </v-list-item-icon>
          </v-list-item>

          <v-list-item-group v-model="selectedItem" color="primary">
            <v-list-item v-for="(script_name, i) in images" :key="i">
              <v-list-item-content>
                <v-list-item-title v-text="script_name"></v-list-item-title>
              </v-list-item-content>
              <v-list-item-icon>
                <v-icon>mdi-palette</v-icon>
            </v-list-item-icon>
            </v-list-item>
          </v-list-item-group>

          <v-subheader>Animations</v-subheader>
          <v-list-item-group v-model="selectedItem" color="primary">
            <v-list-item v-for="(script_name, i) in animations" :key="i" v-on:click="runScript(script_name)">
              <v-list-item-content>
                <v-list-item-title v-text="script_name"></v-list-item-title>
              </v-list-item-content>
              <v-list-item-icon v-on:click="openScript(script_name)">
                <v-icon>mdi-code-braces</v-icon>
              </v-list-item-icon>
            </v-list-item>

            <v-list-item v-on:click="openScript('t555')">
              <v-list-item-content>
                <v-list-item-title>New Script</v-list-item-title>
              </v-list-item-content>
              <v-list-item-icon>
                <v-icon>mdi-plus</v-icon>
              </v-list-item-icon>
            </v-list-item>
          </v-list-item-group>
        </v-list>
      </v-col>
    </v-row>
  </v-container>
</template>

<script>
  import axios from 'axios';

  export default {
    data() {
      return {
        scripts: [],
      }
    },

    computed: {
      animations: function () {
        var animation_scripts = this.scripts.filter(script => {
          return script.type.includes("animation")
        })
        return Array.from(animation_scripts, script => script.name)
      },
      images: function () {
        var image_scripts = this.scripts.filter(script => {
          return script.type.includes("image")
        })
        return Array.from(image_scripts, script => script.name)
      }
    },

    mounted() {
      axios.get('/api/scripts/').then(response => (this.scripts = response.data.scripts))
    },

    methods: {
      runScript: function (script_name) {
        axios.put('/api/runner/run/', {
          name: script_name
        });
      },
      openScript: function (script_name) {
        this.$router.push('/scriptview/' + script_name)
      },
    },
  }
</script>
