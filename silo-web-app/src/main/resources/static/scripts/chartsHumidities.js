var tbody = document.querySelector("tbody");

const timeStamps = [];
const humidityReadings = [];

//retrieve all values from the existing table
tbody.querySelectorAll("tr").forEach(function(row){
    var humidityValue = row.querySelector("td:nth-child(2)").innerText;
    var timeValue = row.querySelector("td:nth-child(3)").innerText;

    //unshift puts the elements in the beginning of the array, thus the newest reading will be at the right-hand part of the chart.
    humidityReadings.unshift(humidityValue);
    timeStamps.unshift(timeValue);
});

const humidityChart = document.getElementById('humLineChart');

//Insert readings in chart when measured
const handleHumJson = (Value, timeStamp) => {
    humidityReadings.unshift(Value);
    timeStamps.unshift(timeStamp);
}
  new Chart(humidityChart, {
    type: 'line',
    data: {
      labels: timeStamps,
      datasets: [{
        label: 'Humidities over time',
        data: humidityReadings,
        borderWidth: 1
      }]
    },
    options: {
      scales: {
        y: {
          beginAtZero: false
        }
      }
    }
});
