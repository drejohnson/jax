open XmlHttpRequest;

type requestMethod =
  | GET
  | POST
  | PUT
  | PATCH
  | DELETE;

let xhr = makeXMLHttpRequest();
let abort = abort;

module Response = {
  let json = responseJson;
  let text = responseText;
  let arrayBuffer = responseArrayBuffer;
  let document = responseDocument;
  let xml = responseXml;
  let url = responseUrl;
  let responseType = setResponseType;
};

let request = (~method, ~url, ~body=?, ~headers=?, ~onSuccess, ~onFail, ()) => {
  let verb =
    switch (method) {
    | GET => "GET"
    | POST => "POST"
    | PUT => "PUT"
    | PATCH => "PATCH"
    | DELETE => "DELETE"
    };

  let handleResponse = () =>
    switch (xhr->readyState, xhr->status) {
    | (Done, 200) => onSuccess(xhr)
    | _ => onFail({"status": xhr->status, "statusText": xhr->statusText})
    };

  xhr->addEventListener(`load(_event => handleResponse()));

  xhr->addEventListener(`error(_event => Js.log("Network Error")));

  xhr->open_(~verb, ~url, ~async=true, ());

  switch (headers) {
  | Some(headers) =>
    headers
    ->Belt.List.map(header => {
        let (k, v) = header;
        xhr->setRequestHeader(k, v);
      })
    ->ignore
  | None => ()
  };

  switch (body) {
  | Some(body) => xhr->sendString(body)
  | None => xhr->send
  };
};