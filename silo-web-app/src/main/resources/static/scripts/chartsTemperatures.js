var tbody = document.querySelector("tbody");

const annotation = window['chartjs-plugin-annotation'];
Chart.register(annotation);

const timeStamps = [];
const temperatureReadings = [];

//retrieve all values from the existing table
tbody.querySelectorAll("tr").forEach(function(row){
    var temperatureValue = row.querySelector("td:nth-child(2)").innerText;
    var timeValue = row.querySelector("td:nth-child(3)").innerText;

    //unshift puts the elements in the beginning of the array, thus the newest reading will be at the right-hand part of the chart.
    temperatureReadings.unshift(temperatureValue);
    timeStamps.unshift(timeValue);
});

const temperatureChart = document.getElementById('tempLineChart');

//Insert readings in chart when measured
const handleTempJson = (Value, timeStamp) => {
    temperatureReadings.unshift(Value);
    timeStamps.unshift(timeStamp);
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
      tooltips: {
        intersect: false,
        mode: 'index'
      },
        plugins: {
          autocolors: false,
          annotation: {
            annotations: {
              bottomLine: {
                type: 'line',
                mode: 'vertical',
                scaleID: 'y',
                value: 20,
                borderColor: 'rgb(0,0,255)',
                borderWidth: 2,
                label: {
                  display: (ctx) => ctx.hovered,
                  content: (ctx) => 'min safe temperature',
                  position: (ctx) => ctx.hoverPosition,
                  backgroundColor: 'rgba(0,0,255,1)'
                },
                enter(ctx, event) {
                  ctx.hovered = true;
                  ctx.hoverPosition = (event.x / ctx.chart.chartArea.width * 82) + '%';
                  ctx.chart.update();
                },
                leave(ctx, event) {
                  ctx.hovered = false;
                  ctx.chart.update();
                }  
              },
              topLine: {
                type: 'line',
                mode: 'vertical',
                scaleID: 'y',
                value: 35,
                borderColor: 'rgb(255,0,0)',
                borderWidth: 2,
                label: {
                  display: (ctx) => ctx.hovered,
                  content: 'max safe temperature',
                  position: (ctx) => ctx.hoverPosition,
                  backgroundColor: 'rgba(255,0,0,1)'
                },
                enter(ctx, event) {
                  ctx.hovered = true;
                  ctx.hoverPosition = (event.x / ctx.chart.chartArea.width * 82) + '%';
                  ctx.chart.update();
                },
                leave(ctx, event) {
                  ctx.hovered = false;
                  ctx.chart.update();
                }  
              }      
            }
          }
        },
      scales: {
        y: {
          beginAtZero: true,
          max: 100
        }
      }  
    }
});

