let xhr = XmlHttpRequest.make();

let request = (~url, ~method, ~body=?, ~headers=?, ~onSuccess, ~onFail, ()) => {
  open XmlHttpRequest;
  let verb =
    switch (method) {
    | GET => "GET"
    | POST => "POST"
    | PUT => "PUT"
    | PATCH => "PATCH"
    | DELETE => "DELETE"
    };

  xhr->readyState === Done && xhr->status === 200
    ? xhr->addEventListener(`load(_event => onSuccess(xhr->response)))
    : xhr->addEventListener(
        `error(
          _event =>
            onFail({"status": xhr->status, "statusText": xhr->statusText}),
        ),
      );

  xhr->open_(verb, url, Some(true), None, None);

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