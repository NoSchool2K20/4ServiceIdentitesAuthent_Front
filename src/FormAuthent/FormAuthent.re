type state = {
    email:string,
    password:string,
    submitted:bool,
    formDisplay:bool,
    pseudo:string,
    name:string,
    surname:string,
    userRole:string,
    error:bool
};

type user = {
    token:string
};
    
[@react.component]
let make = _ => {
    
let (state, setState) = React.useState(()=> {
    email: "",
    password: "",
    submitted: false,
    formDisplay:true,
    pseudo: "",
    name: "",
    surname: "",
    userRole: "",
    error: false
});


let form_authent = 
<form className="container card mt-5"
    onSubmit={event => {
    ReactEvent.Form.preventDefault(event);
    setState(state => {
        ...state,
        submitted: true
    });
    if(state.email != "" && state.password != ""){
        let payload = Js.Dict.empty();
        Js.Dict.set(payload, "email", Js.Json.string(state.email));
        Js.Dict.set(payload, "password", Js.Json.string(state.password));
        let _ = Js.Promise.(
            Fetch.fetchWithInit(
                "https://noschool-authentication.cleverapps.io/connection",
                Fetch.RequestInit.make(
                    ~method_=Post,
                    ~body=Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(payload))),
                    ~headers=Fetch.HeadersInit.make({"Content-Type":"application/json"}),
                    ()
                )
            )
            |> then_(Fetch.Response.json)
            |> then_(json => {
                let res = Json.Decode.{
                    token: json |> field("token",string)
                };
                let ls = Dom.Storage.localStorage;
                Dom.Storage.setItem("token", res.token, ls);
                setState(_ => {
                    email: "", password: "", submitted: false, formDisplay:false, pseudo: "", name: "", surname: "", userRole: "", error: false
                });

                Js.Promise.resolve();
            })
            |> catch(_ => {
                setState(_ => {
                    ...state,
                    error: true
                });
                Js.Promise.resolve();
            })
        );
    
    }
}}>
    <div className="form-group mt-2">
        <label htmlFor="email">"Email"->React.string</label>
        <input name="email" className="form-control" value={state.email} required={true} onChange={event=>{
                let email = ReactEvent.Form.target(event)##value;
                setState(state => {
                    ...state, 
                    email:email
                });
            }}        
        />
    </div>

    <div className="form-group">
        <label htmlFor="password">"Password"->React.string</label>
        <input type_="password" className="form-control" name="password" value={state.password} required={true} onChange={event=>{
                let password = ReactEvent.Form.target(event)##value;
                setState(state => {
                    ...state,
                    password:password
                });
            }}
        />
    </div>

    <div className="form-group">
        <div className="row">
            <div className="col">
                <a type_="button" className="text-primary" onClick={_ => {
                    setState(_ => {
                        email: "", password: "", submitted: false, formDisplay:false, pseudo: "", name: "", surname: "", userRole: "", error: false
                    });
                }}>"Create account"->React.string</a>
            </div>
            <div className="col text-right">
                <input type_="submit" value="Login" className="btn btn-primary"/>
            </div>
        </div>
    </div>

    {(state.error) ? <div className="form-text text-muted">"Something went wrong, please try again"->React.string</div> : ReasonReact.null}
    
</form>;
let form_create = 
<form className="container card mt-5"
    onSubmit={event => {
    ReactEvent.Form.preventDefault(event);
    setState(state =>{
        ...state,
        submitted: true
    });
    if(state.email != "" && state.password != "" && state.pseudo != "" && state.name != "" && state.surname != ""){
        let payload = Js.Dict.empty();
        Js.Dict.set(payload, "email", Js.Json.string(state.email));
        Js.Dict.set(payload, "password", Js.Json.string(state.password));
        Js.Dict.set(payload, "pseudo", Js.Json.string(state.pseudo));
        Js.Dict.set(payload, "name", Js.Json.string(state.name));
        Js.Dict.set(payload, "surname", Js.Json.string(state.surname));
        Js.Dict.set(payload, "userRole", Js.Json.string("Nouveau"));
        let _ = Js.Promise.(
            Fetch.fetchWithInit(
                "https://noschool-authentication.cleverapps.io/users",
                Fetch.RequestInit.make(
                    ~method_=Post,
                    ~body=Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(payload))),
                    ~headers=Fetch.HeadersInit.make({"Content-Type":"application/json"}),
                    ()
                )
            )
            |> then_(Fetch.Response.json)
            |> then_( _ => {
                setState(_ => {
                    email: "", password: "", submitted: false, formDisplay:true, pseudo: "", name: "", surname: "", userRole: "", error: false
                });
                Js.Promise.resolve();
            })
            |> catch(_ => {
                setState(_ => {
                    ...state,
                    error: true
                });
                Js.Promise.resolve();
            })
        );

    }

}}>
    <div className="form-group mt-2">
        <label htmlFor="email">"Email"->React.string</label>
        <input name="email" className="form-control" value={state.email} required={true} onChange={event=>{
                let email = ReactEvent.Form.target(event)##value;
                setState(state => {
                    ...state, 
                    email:email
                });
            }}        
        />
    </div>

    <div className="form-group">
        <label htmlFor="password">"Password"->React.string</label>
        <input type_="password" className="form-control" name="password" value={state.password} required={true} onChange={event=>{
                let password = ReactEvent.Form.target(event)##value;
                setState(state => {
                    ...state,
                    password:password
                });
            }}
        />
    </div>

    <div className="form-group">
        <label htmlFor="pseudo">"Pseudo"->React.string</label>
        <input name="pseudo" className="form-control" value={state.pseudo} required={true} onChange={event=>{
                let pseudo = ReactEvent.Form.target(event)##value;
                setState(state => {
                    ...state, 
                    pseudo:pseudo
                });
            }}        
        />
    </div>

    <div className="form-group">
        <label htmlFor="pseudo">"Name"->React.string</label>
        <input name="name" className="form-control" value={state.name} required={true} onChange={event=>{
                let name = ReactEvent.Form.target(event)##value;
                setState(state => {
                    ...state, 
                    name:name
                });
            }}        
        />
    </div>

    <div className="form-group">
        <label htmlFor="pseudo">"Surname"->React.string</label>
        <input name="surname" className="form-control" value={state.surname} required={true} onChange={event=>{
                let surname = ReactEvent.Form.target(event)##value;
                setState(state => {
                    ...state, 
                    surname:surname
                });
            }}        
        />
    </div>

    <div className="form-group text-right">
        <input type_="submit" value="Create account" className="btn btn-primary"/>
    </div>

    {(state.error) ? <div className="form-text text-muted">"Something went wrong, please try again"->React.string</div> : ReasonReact.null}
</form>;
{(state.formDisplay) ? form_authent : form_create};
};
