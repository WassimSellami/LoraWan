const url = "https://lorawan-application-server.onrender.com/data";
var opts = {
    angle: 0, // The span of the gauge arc
    lineWidth: 0.15, // The line thickness
    radiusScale: 0.9, // Relative radius
    pointer: {
        length: 0.42, // // Relative to gauge radius
        strokeWidth: 0.049, // The thickness
        color: '#000000' // Fill color
    },
    limitMax: false,     // If false, max value increases automatically if value > maxValue
    limitMin: false,     // If true, the min value of the gauge will be fixed
    colorStart: '#6FADCF',   // Colors
    colorStop: '#8FC0DA',    // just experiment with them
    strokeColor: '#E0E0E0',  // to see which ones work best for you
    generateGradient: true,
    highDpiSupport: true,     // High resolution support

};
var target1 = document.getElementById('temperature-gauge'); // your canvas element
var temperatureGauge = new Gauge(target1).setOptions(opts); // create sexy gauge!
temperatureGauge.maxValue = 50; // set max gauge value
temperatureGauge.setMinValue(0);  // Prefer setter over gauge.minValue = 0
temperatureGauge.animationSpeed = 10; // set animation speed (32 is default value)
temperatureGauge.set(0); // set actual value

var target2 = document.getElementById('humidity-gauge'); // your canvas element
var humidityGauge = new Gauge(target2).setOptions(opts); // create sexy gauge!
humidityGauge.maxValue = 100; // set max gauge value
humidityGauge.setMinValue(0);  // Prefer setter over gauge.minValue = 0
humidityGauge.animationSpeed = 10; // set animation speed (32 is default value)
humidityGauge.set(0); // set actual value

$(function () {
    // Handler for .ready() called.
    console.log("Jquery works!");
    getData();
    setInterval(() => {
        getData();
    }, 5000)

});

function getData() {
    $.get(url, function (data) {
        const temperature = data.temperature;
        const humidity = data.humidity;
        const i = data.i;
        $("#temperature-value").text(temperature)
        $("#humidity-value").text(humidity)
        $("#measurement-number").text(i)
        temperatureGauge.set(temperature)
        humidityGauge.set(humidity);
    })
}