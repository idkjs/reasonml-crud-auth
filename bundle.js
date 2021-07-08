const path = require('path')
const { sassPlugin } = require('esbuild-sass-plugin');
const esbuild = require("esbuild");

esbuild.build({
  entryPoints: ['./src/index.bs.js'],
  outfile: "www/js/bundle.js",
  bundle: true,
  minify: true,
  sourcemap: true,
  format: "esm",
  plugins: [sassPlugin({
    // Enabling type: "style" will embed all css in a <style> tag
    // type: "style",
    includePaths: [
      path.resolve(__dirname, "node_modules"),
    ]
  })],
  //this stops esbuild from trying to resolve these things in css, may need to add more types
  external: ["*.svg", "*.woff", "*.css", "*.jpg", "*.png"],
  watch: {
    onRebuild(error, result) {
      if (error) console.error('watch build failed:', error)
      else console.log('watch build succeeded:', result)
    },
  },
}).then(result => {
  // Call "stop" on the result when you're done
  result.stop()
})
