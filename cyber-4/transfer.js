const readline = require('readline');
const _ = require('lodash');
const fs = require('fs');

const inputFile = './input-example';
const outputFile = './output-example';

const rl = readline.createInterface({
 input: fs.createReadStream(inputFile),
 output: process.stdout,
 terminal: false
});

const names = [];

rl.on('line', function (line) {
 names.push(line);
});

rl.on('close', () => {
  const total = [...names];
  total.push(...names.map(l => _.camelCase(l)));
  total.push(...names.map(l => l.replace(' ', '')));
  total.push(...total.map(l => l.toLowerCase()));
  total.push(...total.map(l => l.toUpperCase()));

  fs.writeFile(outputFile, `${total.join('\n')}`, (err) => console.log(err));
})
