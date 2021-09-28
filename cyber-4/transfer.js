// imports
const readline = require('readline'); // line by line
const _ = require('lodash'); // javascript utils
const fs = require('fs'); // work with files

// initialize variables names
const inputFile = './input-example';
const outputFile = './output-example';
const names = [];

// create interface to use events (.on)
const rl = readline.createInterface({
  input: fs.createReadStream(inputFile),
  output: process.stdout,
  terminal: false
});

// after each line
rl.on('line', (line) => names.push(line));

// on finish reading
rl.on('close', () => {
  const total = [...names];
  total.push(...names.map(l => _.camelCase(l))); // Mor Revivo => morRevivo
  total.push(...names.map(l => l.replace(' ', '')));
  total.push(...total.map(l => l.toLowerCase()));
  total.push(...total.map(l => l.toUpperCase()));

  // write the output
  fs.writeFile(outputFile, `${total.join('\n')}`, (err) => console.log(err));
})
