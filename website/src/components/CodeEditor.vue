<template>
  <v-container>
    <v-row class="text-center">
      <v-col class="mb-4">
        <p class="subheading font-weight-regular">
          heya
        </p>
        <v-btn elevation="2" v-on:click="save">
          Save
        </v-btn>
        <v-btn elevation="2" v-on:click="runInEmulator">
          Run in Emulator
        </v-btn>


        <div class="container" style="display: flex; flex: 1;">
          <editor v-model="content" @init="editorInit" width="500" height="500" lang="javascript" theme="monokai"></editor>
        </div>


        <!-- <v-textarea solo v-model="text_editor" name="input-7-4" label="Code Editor"></v-textarea> -->
      </v-col>
    </v-row>
  </v-container>
</template>

<script>
  export default {
    data() {
      return {
        content: "screen.setPixel(0, 0, 'red');\nscreen.setPixel(2, 5, 'green');\nscreen.setPixel(6, 6, 'blue');\nscreen.draw();",
      }
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
        console.log("Save Test Log");
      },

      runInEmulator: function () {
        this.$emit('runInEmulator', this.content)
      },
    }
  }
</script>
