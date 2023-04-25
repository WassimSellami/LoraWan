const express = require("express");
const cors = require('cors');
var bodyParser = require("body-parser");

const app = express();
app.use(cors());
app.use(bodyParser.json());
const port = 3000;

let data={
  temperature:0,
  humidity:0,
  i:-1
};

app.post("/events", (req, res, next) => {
  let body = req.body;
  data = JSON.parse(body.objectJSON);
  console.log(data);
  res.send({
    success: false,
  });
});

app.get("/data", (req, res) => {
  res.send(data);
});

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`);
});
