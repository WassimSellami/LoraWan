const express = require("express");
const app = express();
var bodyParser = require("body-parser");
app.use(bodyParser.json());
const port = 3000;

let data;

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
