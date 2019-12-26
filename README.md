# JAX

> A wrapper around XMLHttpRequest written in ReasonML

## Install

yarn:

```
yarn add https://github.com/drejohnson/jax
```

npm:

```
npm install https://github.com/drejohnson/jax
```

Add `jax` to `bs-dependencies` in `bsconfig.json`.

## Example

```reason
let (data, setData) = React.useState(() => [||]);
React.useEffect0(() => {
  Jax.request(
    ~method_=GET,
    ~url="/api/some/endpoint",
    ~onSuccess=xhr =>
      xhr
        ->Jaxon.Response.json
        ->Js.Nullable.toOption
        ->Belt.Option.map(res => setData(_ => res->parseResponse))
        ->ignore,
    ~onFail=err => Js.log(err),
    (),
  );
  Some(() => {Jax.xhr->Jax.abort});
})
```
