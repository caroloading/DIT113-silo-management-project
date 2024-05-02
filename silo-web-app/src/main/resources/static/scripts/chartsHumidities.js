var tbody = document.querySelector("tbody");

const gradient = window['chartjs-plugin-gradient'];
Chart.register(gradient);

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

const humidityChart = document.getElementById('humBarChart');

//Insert readings in chart when measured
const handleHumJson = (Value, timeStamp) => {
    humidityReadings.unshift(Value);
    timeStamps.unshift(timeStamp);
}
  new Chart(humidityChart, {
    type: 'bar',
    data: {
      labels: timeStamps,
      datasets: [{
        label: 'Humiditiy Level',
        data: humidityReadings,
        borderWidth: 1,
        gradient: {
          backgroundColor: {
              axis: 'y',
              colors: {
                  0: '#DAF7A6',
                  20: '#FEE08C',
                  30: '#F8AD48'
              }
          },
          borderColor: {
              axis: 'x',
              colors: {

              }
          }
      }
      }]
    },
    options: {
      scales: {
        y: {
          max: 100,
          min: 0
        }
      }
    }
});
