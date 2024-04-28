const socket = new SockJS("/silo-websocket")
const stompClient = Stomp.over(socket);

const onConnect = () => {
    stompClient.subscribe("/topic/temperatures/update", onReceivedTempMessage);
    stompClient.subscribe("/topic/humidity/update", onReceivedHumMessage);
    stompClient.subscribe("/topic/distances/update", onReceivedDistMessage);
}

const onError = () => {
    console.log("Could not establish WebSocket connection");
}

stompClient.connect({}, onConnect, onError);

const onReceivedTempMessage = (payload) => {
    const payloadBody = JSON.parse(payload.body);

    const card = document.getElementById("temp-elem");
    card.textContent = payloadBody.tvalue;
}

const onReceivedHumMessage = (payload) => {
    const payloadBody = JSON.parse(payload.body);

    const card = document.getElementById("humid-elem");
    card.textContent = payloadBody.hvalue;
}

const onReceivedDistMessage = (payload) => {
    const payloadBody = JSON.parse(payload.body);

    const card = document.getElementById("grain-elem");
    card.textContent = payloadBody.height;
}