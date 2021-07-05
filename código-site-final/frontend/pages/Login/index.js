import { useRouter } from 'next/router'
import styles from '../../styles/Login.module.css'
import { useState } from 'react';
import Head from 'next/head';
import apilogin from '../../services/apilogin'
import Swal from 'sweetalert2'

export default function Login(){
    const router = useRouter()
    const [login, setLogin] = useState('')
    const [password, setPassword] = useState('')

     async function handleLogin(){
        try{
            const response = await apilogin.get('api/login', {
              auth:
                { username: login,
                  password: password
                }
            })

            if(response){
                localStorage.setItem("token", response.data.token);
                
                router.push('/Home')
            }
        }
        catch{
                Swal.fire({
                    icon: 'error',
                    title: 'Oops...',
                    text: 'Os dados digitados estão incorretos'
                })          
        }
    } 

    return(
        <div className={styles.loginContainer}>
            <Head>
                <title>Cadastro Pet</title>
                <link rel="icon" href="/qr.svg" />
            </Head>
            <main className={styles.loginMain}>
                <img className={styles.logo} src="logo.svg"/>
                <section className={styles.inputSection}>
                    <input 
                        type="text" 
                        placeholder="E-mail" 
                        onChange={(e) => setLogin(e.target.value)}
                        className={styles.loginInput} 
                    />
                    <input 
                        type="password" 
                        placeholder="Senha"                         
                        onChange={(e) => setPassword(e.target.value)}
                        className={styles.loginInput} 
                    />
                </section>
                <div className={styles.loginButton} onClick={handleLogin}>
                    <img 
                        width="30px" 
                        src="login.svg" 
                        alt="Login"   
                    />
                </div>
            </main>
        </div>
    )
}