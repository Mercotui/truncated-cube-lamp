<template>
  <v-container>
    <v-row class="text-center">
      <v-col class="mb-4">
        <v-list dense>
          <v-subheader>Images</v-subheader>
          <v-list-item-group v-model="selectedItem" color="primary">
            <v-list-item v-for="(script_name, i) in scripts" :key="i">
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
            <v-list-item v-for="(script_name, i) in scripts" :key="i" v-on:click="run(script_name)">
              <v-list-item-content>
                <v-list-item-title v-text="script_name"></v-list-item-title>
              </v-list-item-content>
              <v-list-item-icon>
                <v-icon>mdi-code-braces</v-icon>
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

    mounted() {
      axios.get('/api/scripts/').then(response => (this.scripts = response.data.scripts))
    },

    methods: {
      run: function (script_name) {
        axios.put('/api/runner/run/', {
          name: script_name
        });
      },
    },
  }
</script>
