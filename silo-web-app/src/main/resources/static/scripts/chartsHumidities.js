var tbody = document.querySelector("tbody");
const socket = new SockJS("/silo-websocket")
const stompClient = Stomp.over(socket);

const url = window.location.href.split("/");
const urlPath = url[url.length - 1]

const gradient = window['chartjs-plugin-gradient'];
Chart.register(gradient);

const onConnect = () => {
    stompClient.subscribe("/topic/humidity/update", (payload) => onReceivedMessage(payload, "humidity"))
};

const onError = () => {
  console.log("Could not establish WebSocket connection");
}

stompClient.connect({}, onConnect, onError);

const insertIntoTable = (data) => {
  const table = document.getElementById('humidity-table');

  const tableBody = table.getElementsByTagName("tbody")[0];

  let newRow = tableBody.insertRow(0);

  let idCell = newRow.insertCell();
  idCell.appendChild(document.createTextNode(data.id))

  let temperatureCell = newRow.insertCell();
  temperatureCell.appendChild(document.createTextNode(data.value));

  let datetimeCell = newRow.insertCell();
  datetimeCell.appendChild(document.createTextNode(data.dateTime));
}

const onReceivedMessage = (payload) => {
  const payloadBody = JSON.parse(payload.body);
  insertIntoTable({id: payloadBody.id, value: payloadBody.hvalue, dateTime: payloadBody.dateTime});

  var humidityValue = payloadBody.hvalue;
  var timeValue = payloadBody.dateTime;

  humidityReadings.push(humidityValue);
  timeStamps.push(timeValue);
  update();
}

const timeStamps = [];
const humidityReadings = [];

//retrieve all values from the existing table
function handleHumJson() {
  tbody.querySelectorAll("tr").forEach(function(row){
      var humidityValue = row.querySelector("td:nth-child(2)").innerText;
      var timeValue = row.querySelector("td:nth-child(3)").innerText;

      //unshift puts the elements in the beginning of the array, thus the newest reading will be at the right-hand part of the chart.
      humidityReadings.unshift(humidityValue);
      timeStamps.unshift(timeValue);
  });
}

if(timeStamps.length == 0){
  handleHumJson();
}

const humidityChart = document.getElementById('humBarChart');

  var humChart = new Chart(humidityChart, {
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

function update(){
  humChart.update();
}