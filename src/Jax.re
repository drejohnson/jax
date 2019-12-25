type requestMethod =
  | GET
  | POST
  | PUT
  | PATCH
  | DELETE;

let xhr = XmlHttpRequest.makeXMLHttpRequest();

let abort = XmlHttpRequest.abort;

let request = (~method, ~url, ~body=?, ~headers=?, ~onSuccess, ~onFail, ()) => {
  open XmlHttpRequest;
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
    | (Done, 200) => onSuccess(. xhr->response)
    | _ => onFail(. {"status": xhr->status, "statusText": xhr->statusText})
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