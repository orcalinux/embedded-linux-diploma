async function checkStatus() {
  try {
    let response = await fetch("/push-button");
    let data = await response.json();

    const statusElem = document.getElementById("button-status");
    if (data.pressed) {
      statusElem.textContent = "Button is pressed!";
      statusElem.style.color = "red";
    } else {
      statusElem.textContent = "Button is not pressed.";
      statusElem.style.color = "green";
    }
  } catch (err) {
    console.error(err);
    document.getElementById("button-status").textContent =
      "Error fetching status.";
  }
}

// Optionally check status automatically every few seconds:
// setInterval(checkStatus, 2000);
