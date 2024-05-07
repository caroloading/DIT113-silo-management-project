const gradient = window['chartjs-plugin-gradient']
const annotation = window['chartjs-plugin-annotation']
Chart.register(annotation);
Chart.register(gradient);

var currentChart;

var dataReadings = [];
var timeStamps = [];

getTableData();

if (window.location.href.includes('humidities')){
  const humidityChart = document.getElementById('humBarChart');

  currentChart = new Chart(humidityChart, {
    type: 'bar',
    data: {
      labels: timeStamps,
      datasets: [{
        label: 'Humiditiy Level',
        data: dataReadings,
        borderWidth: 0,
        gradient: {
          backgroundColor: {
            axis: 'y',
            colors: {
              0: '#DAF7A6',
              20: '#FEE08C',
              30: '#F8AD48'
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
    },
  });
}
else if (window.location.href.includes('temperatures')){
  const temperatureChart = document.getElementById('tempLineChart');

  currentChart = new Chart(temperatureChart, {
    type: 'line',
    data: {
      labels: timeStamps,
      datasets: [{
        label: 'Temperatures over time',
        data: dataReadings,
        borderWidth: 1
      }]
    },
    options: {
      tooltips: {
        intersect: false,
        mode: 'index',
        responsive: true
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
                borderWidth: 4,
                label: {
                  display: (ctx) => ctx.hovered,
                  content: 'min safe temperature',
                  position: (ctx) => ctx.hoverPosition,
                  backgroundColor: 'rgba(0,0,255,1)'
                },
                enter(ctx, event) {
                  ctx.hovered = true;
                  ctx.hoverPosition = (event.x / ctx.chart.chartArea.width * 82) + '%';
                  ctx.chart.update();
                },
                leave(ctx) {
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
                borderWidth: 4,
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
                leave(ctx) {
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
}
else if (window.location.href.includes('grainheights')){

  const heightChart = document.getElementById('heightChart');

  currentChart = new Chart(heightChart,{
    type: 'bar',
    data: {
    labels: timeStamps,
        datasets: [{
        label: 'grain level',
        data: dataReadings,
        borderWidth: 0,
        gradient: {
          backgroundColor: {
            axis: 'y',
            colors: {
              0: '#DAF7A6',
              70: '#FEE08C',
              85: '#F8AD48'
            }
          }
        }
      }]
    },
    options: {
        scales: {
            y: {
                min: 0,
                max: 100,
            }
        }
    },
  });
}

function getTableData() {
    document.querySelectorAll(".chartLabel").forEach((e) => {
      var timeValue = e.innerHTML;
      timeStamps.unshift(timeValue); //unshift puts the elements in the beginning of the array, thus the newest reading will be at the right-hand part of the chart.
    }),
    document.querySelectorAll(".chartData").forEach((e) => {
      var Value = e.innerHTML;
      dataReadings.unshift(Value); //unshift puts the elements in the beginning of the array, thus the newest reading will be at the right-hand part of the chart.
    })
}

function updateChart(value, time) {
  dataReadings.push(value);
  timeStamps.push(time);
  currentChart.update();
}