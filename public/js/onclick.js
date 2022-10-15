function compl_get() {
    var input_form = document.querySelector(".formGET .namePerson");
    var params = "namePerson=" + input_form.value;

    var xhr = new XMLHttpRequest();
        xhr.open("GET", "/api/form?" + params, false);
        xhr.send();

    alert(xhr.responseText);
}

function compl_post() {
    var input_form = document.querySelector(".formPOST .namePerson");
    var params = "namePerson=" + input_form.value;

    var xhr = new XMLHttpRequest();
        xhr.open("POST", "/api/form?" + params, false);
        xhr.send();

    alert(xhr.responseText);
}