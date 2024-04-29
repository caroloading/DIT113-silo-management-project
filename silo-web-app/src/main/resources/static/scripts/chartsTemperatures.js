var tbody = document.querySelector("tbody");

const timeStamps = [];
const temperatureReadings = [];

//retrieve all values from the existing table
tbody.querySelectorAll("tr").forEach(function(row){
    var temperatureValue = row.querySelector("td:nth-child(2)").innerText;
    var timeValue = row.querySelector("td:nth-child(3)").innerText;

    temperatureReadings.push(temperatureValue);
    timeStamps.push(timeValue);
});

const temperatureChart = document.getElementById('myChart');

//Insert readings in chart when measured
const handleJson = (Value, timeStamp) => {
    temperatureReadings.push(Value);
    timeStamps.push(timeStamp);
}
  new Chart(temperatureChart, {
    type: 'line',
    data: {
      labels: timeStamps,
      datasets: [{
        label: 'Temperatures over time',
        data: temperatureReadings,
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


