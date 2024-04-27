const socket = new SockJS("/silo-websocket")
const stompClient = Stomp.over(socket);

const onConnect = () => {
    stompClient.subscribe("/topic/humidity/update",  onReceivedMessage);
}

const onError = () => {
    console.log("Could not establish WebSocket connection");
}

stompClient.connect({}, onConnect, onError);

const insertIntoHumidityTable = (payloadBody) => {
    const tableBody = document.getElementById("humidity-table").getElementsByTagName("tbody")[0];

    let newRow = tableBody.insertRow(0);

    let idCell = newRow.insertCell();
    idCell.appendChild(document.createTextNode(payloadBody.id))

    let temperatureCell = newRow.insertCell();
    temperatureCell.appendChild(document.createTextNode(payloadBody.hvalue));

    let datetimeCell = newRow.insertCell();
    datetimeCell.appendChild(document.createTextNode(payloadBody.dateTime));
}

const onReceivedMessage = (payload) => {
    const payloadBody = JSON.parse(payload.body);

    insertIntoHumidityTable(payloadBody);
}
