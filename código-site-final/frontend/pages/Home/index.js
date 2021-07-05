import styles from '../../styles/Home.module.css'
import { UserBox } from '../../components/UserBox/UserBox'
import { FiPower } from 'react-icons/fi';
import { ButtonRegister } from '../../components/ButtonRegister/ButtonRegister'
import { useEffect, useState } from 'react';
import { useRouter } from 'next/router';
import socket from '../../services/socketio';
import { StatusSocketIO } from '../../components/StatusSocketIO';

export default function Home(){
    const router = useRouter();
    const [logado, setLogado] = useState(true);
    const [users, setUsers] = useState([])

    useEffect(() => {
        socket.emit("downloadusuarios");

        socket.on('download_usuarios', (info) => {
            console.log(info)
            setUsers(info)
        })
    },[])

    // useEffect(() => {
    //     const token = localStorage.getItem("token")
    //     if(!token){
    //         router.push('/');
    //     }else{
    //         localStorage.removeItem("token");
    //         setLogado(true)
    //     }

    // }, [])

    function Logout(){
        router.push('/');
    }

    return(     
        <div className={styles.container}>
            {
                logado && 
                <>
                    <div className={styles.header}>
                        <img src="logo.svg" alt="logo pet"/>
                        
                        <div className={styles.buttons}>
                            <ButtonRegister />
                            <button onClick={Logout} className={styles.powerOff}>
                                <FiPower color={'#17A2B8'} size={'1.85rem'} strokeWidth={2.5}/>
                            </button>
                        </div>
                    </div>
                    <div className={styles.content}>
                        {users.map((user, index) => (
                            <UserBox 
                                name={user?.name} 
                                id={user?.id} 
                                key={user?.id}
                                card={user?.card}
                                biometry={user?.biometry}
                            />
                        ))}
                        
                    </div>
                    <StatusSocketIO />
                </>
            }
            
        </div>     
    )
}