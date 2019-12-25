# JAX

> A wrapper around XMLHttpRequest written in ReasonML

## Install

yarn:

```
yarn add jax
```

npm:

```
npm install jax
```

Add `jax` to `bs-dependencies` in `bsconfig.json`.

## Example

```reason
let (data, setData) = React.useState(() => [||]);
React.useEffect0(() => {
  Jax.request(
    ~method_=GET,
    ~url="/api/some/endpoint",
    ~onSuccess=res => setData(_ => res),
    ~onFail=err => Js.log(err),
    (),
  );
  Some(() => {Jax.xhr->Jax.abort});
})
```
