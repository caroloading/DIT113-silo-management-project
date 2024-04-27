const socket = new SockJS("/silo-websocket")
const stompClient = Stomp.over(socket);

const onConnect = () => {
    stompClient.subscribe("/topic/temperatures/update", onReceivedMessage);
}

const onError = () => {
    console.log("Could not establish WebSocket connection");
}

const onReceivedMessage = (payload) => {
    const payloadBody = JSON.parse(payload.body);

    console.log(payloadBody);
    insertIntoTemperatureTable(payloadBody);
}

stompClient.connect({}, onConnect, onError);

function insertIntoTemperatureTable(payloadBody) {
    const tableBody = document.getElementById("temperature-table").getElementsByTagName("tbody")[0];

    let newRow = tableBody.insertRow(0);

    let idCell = newRow.insertCell();
    idCell.appendChild(document.createTextNode(payloadBody.id))

    let temperatureCell = newRow.insertCell();
    temperatureCell.appendChild(document.createTextNode(payloadBody.tvalue));

    let datetimeCell = newRow.insertCell();
    datetimeCell.appendChild(document.createTextNode(payloadBody.dateTime));
}
