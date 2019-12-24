# JAX

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
  let request = Jax.request(
    ~method_=GET,
    ~url="/api/some/endpoint",
    ~onSucces=res => setData(_ => res));
  Some(() => {
    request->Jax.abort
  })
})
```
