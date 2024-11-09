<template>
  <v-container>
    <v-row class="text-center">
      <v-col class="mb-4">
        <v-overlay v-model="save_overlay_opened">
          <v-card class="mx-auto my-12" style="right: 50vw; left: 50vw" max-width="374">
            <v-card-title>Enter Script Name</v-card-title>
            <v-text-field label="Script Name" model-value="script_name" solo></v-text-field>
            <v-card-actions>
              <v-btn @click="save_overlay_opened = false">
                Cancel
              </v-btn>
              <v-btn color="success" @click="saveAs">
                Save
              </v-btn>
            </v-card-actions>
          </v-card>
        </v-overlay>

        <div class="text-center">
          <v-btn class="mx-1" elevation="2" :disabled="!save_enabled" v-on:click="save">Save</v-btn>
          <v-btn class="mx-1" elevation="2" v-on:click="save_overlay_opened = true">Save As</v-btn>
          <v-btn class="mx-1" elevation="2" :disabled="!delete_enabled" color="error"
                 v-on:click="delete_overlay_opened = true">Delete
          </v-btn>
          <v-btn class="mx-1" elevation="2" color="success" v-on:click="runInEmulator">Run in Emulator</v-btn>
        </div>

        <v-overlay :value="delete_overlay_opened">
          <v-card class="mx-auto my-12" max-width="374">
            <v-card-title>Delete {{ script_name }} ?</v-card-title>
            <v-card-actions>
              <v-btn @click="delete_overlay_opened = false">
                Cancel
              </v-btn>
              <v-btn color="error" @click="deleteScript">
                Delete
              </v-btn>
            </v-card-actions>
          </v-card>
        </v-overlay>

        <div id="monaco-container" style="text-align: left; display: flex; flex: 1; overflow: hidden; height: 60vh"></div>
        <!-- <v-textarea solo v-model="content" name="input-7-4" label="Code Editor"></v-textarea> -->
      </v-col>
    </v-row>
  </v-container>
</template>

<script>
import axios from 'axios';
import base64 from 'base-64';
import utf8 from 'utf8';

import * as monaco from 'monaco-editor'
import editorWorker from 'monaco-editor/esm/vs/editor/editor.worker?worker'
import tsWorker from 'monaco-editor/esm/vs/language/typescript/ts.worker?worker'

export default {
  editor: null,

  data() {
    return {
      save_overlay_opened: false,
      delete_overlay_opened: false,
      type: ["template"],
      content: "Loading",
    }
  },

  computed: {
    save_enabled: function () {
      return !(this.type.includes("default") || this.type.includes("template") || this.script_name === "")
    },
    delete_enabled: function () {
      return !(this.type.includes("default") || this.type.includes("template"))
    },
  },

  props: {
    script_name: String
  },

  mounted() {
    self.MonacoEnvironment = {
      getWorker(_, label) {
        if (label === 'typescript' || label === 'javascript') {
          return new tsWorker()
        }
        return new editorWorker()
      }
    }

    this.editor = monaco.editor.create(document.getElementById('monaco-container'), {
      value: "Loading",
      language: 'javascript',
      theme: "vs-dark",
    });

    if(this.script_name) {
      axios.get('/api/scripts/' + this.script_name + '/').then(response => {
        const bytes = base64.decode(response.data.script);
        const decoded_script = utf8.decode(bytes);
        this.editor.setValue(decoded_script);
        this.type = response.data.type;
      });
    } else {
      this.editor.setValue("");
    }
  },

  methods: {
    save: function () {
      var bytes = utf8.encode(this.editor.getValue());
      var encoded_script = base64.encode(bytes);

      axios.put('/api/scripts/' + this.script_name + '/', {
        name: this.script_name,
        script: encoded_script,
        type: this.type,
      });
    },

    saveAs: function () {
      this.save_overlay_opened = false;
      this.type = ["animation"]
      this.save();
      this.$router.push('/script/' + this.script_name);
    },

    deleteScript: function () {
      axios.delete('/api/scripts/' + this.script_name + '/').then(() => {
        this.$router.push('/');
      });
    },

    runInEmulator: function () {
      this.$emit('runInEmulator', this.editor.getValue())
    },
  }
}
</script>
