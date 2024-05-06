var tbody = document.querySelector("tbody");
const socket = new SockJS("/silo-websocket")
const stompClient = Stomp.over(socket);

const url = window.location.href.split("/");
const urlPath = url[url.length - 1]

const onConnect = () => {
    stompClient.subscribe("/topic/temperatures/update", (payload) => onReceivedMessage(payload, "temperature"))
};

const onError = () => {
  console.log("Could not establish WebSocket connection");
}

stompClient.connect({}, onConnect, onError);

const insertIntoTable = (data) => {
  const table = document.getElementById('temperature-table');

  const tableBody = table.getElementsByTagName("tbody")[0];

  let newRow = tableBody.insertRow(0);

  let idCell = newRow.insertCell();
  idCell.classList.add("tableColumn1");
  idCell.appendChild(document.createTextNode(data.id))

  let temperatureCell = newRow.insertCell();
  temperatureCell.classList.add("tableColumn1");
  temperatureCell.appendChild(document.createTextNode(data.value));

  let datetimeCell = newRow.insertCell();
  datetimeCell.appendChild(document.createTextNode(data.dateTime));
}

const onReceivedMessage = (payload) => {
  const payloadBody = JSON.parse(payload.body);
  insertIntoTable({id: payloadBody.id, value: payloadBody.tvalue, dateTime: payloadBody.dateTime});

  var temperatureValue = payloadBody.tvalue;
  var timeValue = payloadBody.dateTime;

  temperatureReadings.push(temperatureValue);
  timeStamps.push(timeValue);
  update();
}

const annotation = window['chartjs-plugin-annotation'];
Chart.register(annotation);

const timeStamps = [];
const temperatureReadings = [];

//retrieve all values from the existing table
function handleTempJson() {
  tbody.querySelectorAll("tr").forEach(function(row){
    var temperatureValue = row.querySelector("td:nth-child(2)").innerText;
    var timeValue = row.querySelector("td:nth-child(3)").innerText;

    //unshift puts the elements in the beginning of the array, thus the newest reading will be at the right-hand part of the chart.
    temperatureReadings.unshift(temperatureValue);
    timeStamps.unshift(timeValue);
  });
}

if(timeStamps.length == 0){
  handleTempJson();
}

const temperatureChart = document.getElementById('tempLineChart');

  var tempChart = new Chart(temperatureChart, {
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

function update(){
  tempChart.update();
}