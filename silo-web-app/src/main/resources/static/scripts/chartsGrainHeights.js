var tbody = document.querySelector("tbody");
const socket = new SockJS("/silo-websocket")
const stompClient = Stomp.over(socket);

const url = window.location.href.split("/");
const urlPath = url[url.length - 1]

const gradient = window['chartjs-plugin-gradient'];
Chart.register(gradient);

const onConnect = () => {
    stompClient.subscribe("/topic/distances/update", (payload) => onReceivedMessage(payload, "distance"))
};

const onError = () => {
  console.log("Could not establish WebSocket connection");
}

stompClient.connect({}, onConnect, onError);

const insertIntoTable = (data) => {
  const table = document.getElementById('distance-table');

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
  insertIntoTable({id: payloadBody.id, value: payloadBody.height, dateTime: payloadBody.dateTime});

  var heightValue = payloadBody.height;
  var timeValue = payloadBody.dateTime;

  heightReadings.push(heightValue);
  timeStamps.push(timeValue);
  update();
}

const timeStamps = [];
const heightReadings = [];

function handleGrainJson() {
    tbody.querySelectorAll("tr").forEach(function(row){
    var heightValue = (row.querySelector("td:nth-child(2)").innerText/15)*(-100)+100;//turn grain height into to a percentage (15 is the max in this scale meaning silo is empty/0%)
    var timeValue = row.querySelector("td:nth-child(3)").innerText;

    //unshift puts the elements in the beginning of the array, thus the newest reading will be at the right-hand part of the chart.
    heightReadings.unshift(heightValue);
    timeStamps.unshift(timeValue);
    });
}

if(timeStamps.length == 0){
    handleGrainJson();
}

const grainHeightChart = document.getElementById('heightChart');

var grainChart = new Chart(grainHeightChart,{
    type: 'bar',
    data: {
    labels: timeStamps,
        datasets: [{
        label: 'grain level',
        data: heightReadings,
        borderWidth: 0,
            gradient: {
                backgroundColor: {
                    axis: 'y',
                    colors: {
                        0: '#DAF7A6',
                        70: '#FEE08C',
                        100: '#F8AD48'
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
                min: 0,
                max: 100,
            }
        }
    }
});

function update(){
    grainChart.update();
  }
