const express = require('express');
const app = express();

// Serve static files from the public directory
app.use(express.static('ui'));

// Route handler to serve the HTML file
app.get('/', (req, res) => {
  res.sendFile(__dirname + './ui/main.html');
});

app.get('/', (req, res) => {
  res.send('Hello World!');
});
