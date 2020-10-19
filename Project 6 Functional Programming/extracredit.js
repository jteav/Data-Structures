//Johnathan Teav
//This program prints a picture from dogs.json to the terminal.
//It takes a command line argument from 1 - 19.
const R = require('ramda'); //npm install ramda
const got = require('got');
const terminalImage = require('terminal-image');    //npm install terminal-image
const fs = require('fs');

const flickrDataDog = JSON.parse(fs.readFileSync('dogs.json', 'utf8'));

//Returns the image link
const image = R.compose(
	R.map(R.prop('m')),
	R.map(R.prop('media')),
	R.prop('items')
);

//The assignment wanted to print images 0 - 19, but image 0 is no longer available.
//input only picks 1 - 19 now.
let input = process.argv[2];
if(input < 1 || input > 19){
	input = 1;
}

(async () => {
	const {body} = await got(R.compose(R.nth(input)) (image(flickrDataDog)), {encoding: null});
	console.log(await terminalImage.buffer(body));
})();