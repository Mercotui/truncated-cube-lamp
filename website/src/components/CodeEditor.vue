<template>
  <v-container>
    <v-row class="text-center">
      <v-col class="mb-4">
        <p class="subheading font-weight-regular">
          heya
        </p>
        <v-btn elevation="2" v-on:click="save">Save</v-btn>
        <v-btn elevation="2" v-on:click="overlay_opened = true">Save As</v-btn>
        <v-btn elevation="2" v-on:click="runInEmulator">Run in Emulator</v-btn>

        <v-overlay :value="overlay_opened">
          <v-card class="mx-auto my-12" max-width="374">
            <v-card-title>Enter Script Name</v-card-title>
            <v-text-field label="Script Name" v-model="script_name" solo></v-text-field>
            <v-card-actions>
              <v-btn color="primary" @click="overlay_opened = false">
                Cancel
              </v-btn>
              <v-btn color="success" @click="saveAs">
                Save
              </v-btn>
            </v-card-actions>
          </v-card>
        </v-overlay>


        <div class="container" style="display: flex; flex: 1;">
          <editor v-model="content" @init="editorInit" width="500" height="500" lang="javascript" theme="monokai"></editor>
        </div>


        <!-- <v-textarea solo v-model="text_editor" name="input-7-4" label="Code Editor"></v-textarea> -->
      </v-col>
    </v-row>
  </v-container>
</template>

<script>
import axios from 'axios';
import base64 from 'base-64';
import utf8 from 'utf8';

  export default {
    data() {
      return {
        overlay_opened: false,
        content: "screen.setPixel(0, 0, 'red');\nscreen.setPixel(2, 5, 'green');\nscreen.setPixel(6, 6, 'blue');\nscreen.draw();",
      }
    },

    props: {
      script_name: String
    },

    components: {
        editor: require('vue2-ace-editor'),
    },

    methods: {
      editorInit: function (editor) {
        require('brace/ext/language_tools') //language extension prerequsite...
        require('brace/mode/javascript')    //language
        require('brace/mode/less')
        require('brace/theme/monokai')
        require('brace/snippets/javascript') //snippet
        editor.setOptions({
            maxLines: 30,
            wrap: true,
            enableBasicAutocompletion: true,
            autoScrollEditorIntoView: true
        });
      },

      save: function () {
        var bytes = utf8.encode(this.content);
        var encoded_script = base64.encode(bytes);

        axios.put('/api/scripts/' + this.script_name + '/', {
          script: encoded_script
        });
      },

      saveAs: function () {
        this.overlay_opened = false;
        this.save();
      },

      runInEmulator: function () {
        this.$emit('runInEmulator', this.content)
      },
    }
  }
</script>
